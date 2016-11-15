
/*-------------------------------------------------------------*/
/*--- Block sorting machinery                               ---*/
/*---                                           blocksort.c ---*/
/*-------------------------------------------------------------*/

/* ------------------------------------------------------------------
   This file is part of bzip2/libbzip2, a program and library for
   lossless, block-sorting data compression.

   bzip2/libbzip2 version 1.0.6 of 6 September 2010
   Copyright (C) 1996-2010 Julian Seward <jseward@bzip.org>

   Please read the WARNING, DISCLAIMER and PATENTS sections in the 
   README file.

   This program is released under the terms of the license contained
   in the file LICENSE.
   ------------------------------------------------------------------ */


#include "bzlib_private.h"

/*---------------------------------------------*/
/*--- Fallback O(N log(N)^2) sorting        ---*/
/*--- algorithm, for repetitive blocks      ---*/
/*---------------------------------------------*/

/*---------------------------------------------*/








#define BIGFREQ(b) (ftab[((b)+1) << 8] - ftab[(b) << 8])
#define SETMASK (1 << 21)
#define CLEARMASK (~(SETMASK))


static
void mainSort ( UInt32* ptr, 
                UChar*  block,
                UInt16* quadrant, 
                UInt32* ftab,
                Int32   nblock,
                Int32   verb,
                Int32*  budget )
{
   Int32  i, j, k, ss, sb;
   Int32  runningOrder[256];
   Bool   bigDone[256];
   Int32  copyStart[256];
   Int32  copyEnd  [256];
   UChar  c1;
   Int32  numQSorted;
   UInt16 s;
   if (verb >= 4) VPrintf0 ( "        main sort initialise ...\n" );

   /*-- set up the 2-byte frequency table --*/
   for (i = 65536; i >= 0; i--) ftab[i] = 0;

   j = block[0] << 8;
   i = nblock-1;
   for (; i >= 3; i -= 4) {
      quadrant[i] = 0;
      j = (j >> 8) | ( ((UInt16)block[i]) << 8);
      ftab[j]++;
      quadrant[i-1] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-1]) << 8);
      ftab[j]++;
      quadrant[i-2] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-2]) << 8);
      ftab[j]++;
      quadrant[i-3] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-3]) << 8);
      ftab[j]++;
   }
   for (; i >= 0; i--) {
      quadrant[i] = 0;
      j = (j >> 8) | ( ((UInt16)block[i]) << 8);
      ftab[j]++;
   }

   /*-- (emphasises close relationship of block & quadrant) --*/
   for (i = 0; i < BZ_N_OVERSHOOT; i++) {
      block   [nblock+i] = block[i];
      quadrant[nblock+i] = 0;
   }

   if (verb >= 4) VPrintf0 ( "        bucket sorting ...\n" );

   /*-- Complete the initial radix sort --*/
   for (i = 1; i <= 65536; i++) ftab[i] += ftab[i-1];

   s = block[0] << 8;
   i = nblock-1;
   for (; i >= 3; i -= 4) {
      s = (s >> 8) | (block[i] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i;
      s = (s >> 8) | (block[i-1] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-1;
      s = (s >> 8) | (block[i-2] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-2;
      s = (s >> 8) | (block[i-3] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-3;
   }
   for (; i >= 0; i--) {
      s = (s >> 8) | (block[i] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i;
   }

   /*--
      Now ftab contains the first loc of every small bucket.
      Calculate the running order, from smallest to largest
      big bucket.
   --*/
   for (i = 0; i <= 255; i++) {
      bigDone     [i] = False;
      runningOrder[i] = i;
   }

   {
      Int32 vv;
      Int32 h = 1;
      do h = 3 * h + 1; while (h <= 256);
      do {
         h = h / 3;
         for (i = h; i <= 255; i++) {
            vv = runningOrder[i];
            j = i;
            while ( BIGFREQ(runningOrder[j-h]) > BIGFREQ(vv) ) {
               runningOrder[j] = runningOrder[j-h];
               j = j - h;
               if (j <= (h - 1)) goto zero;
            }
            zero:
            runningOrder[j] = vv;
         }
      } while (h != 1);
   }

   /*--
      The main sorting loop.
   --*/

   numQSorted = 0;

   for (i = 0; i <= 255; i++) {

      /*--
         Process big buckets, starting with the least full.
         Basically this is a 3-step process in which we call
         mainQSort3 to sort the small buckets [ss, j], but
         also make a big effort to avoid the calls if we can.
      --*/
      ss = runningOrder[i];

      /*--
         Step 1:
         Complete the big bucket [ss] by quicksorting
         any unsorted small buckets [ss, j], for j != ss.  
         Hopefully previous pointer-scanning phases have already
         completed many of the small buckets [ss, j], so
         we don't have to sort them at all.
      --*/
      for (j = 0; j <= 255; j++) {
         if (j != ss) {
            sb = (ss << 8) + j;
            if ( ! (ftab[sb] & SETMASK) ) {
               Int32 lo = ftab[sb]   & CLEARMASK;
               Int32 hi = (ftab[sb+1] & CLEARMASK) - 1;
               if (hi > lo) {
                  if (verb >= 4)
                     VPrintf4 ( "        qsort [0x%x, 0x%x]   "
                                "done %d   this %d\n",
                                ss, j, numQSorted, hi - lo + 1 );
                  mainQSort3 ( 
                     ptr, block, quadrant, nblock, 
                     lo, hi, BZ_N_RADIX, budget 
                  );   
                  numQSorted += (hi - lo + 1);
                  if (*budget < 0) return;
               }
            }
            ftab[sb] |= SETMASK;
         }
      }

      AssertH ( !bigDone[ss], 1006 );

      /*--
         Step 2:
         Now scan this big bucket [ss] so as to synthesise the
         sorted order for small buckets [t, ss] for all t,
         including, magically, the bucket [ss,ss] too.
         This will avoid doing Real Work in subsequent Step 1's.
      --*/
      {
         for (j = 0; j <= 255; j++) {
            copyStart[j] =  ftab[(j << 8) + ss]     & CLEARMASK;
            copyEnd  [j] = (ftab[(j << 8) + ss + 1] & CLEARMASK) - 1;
         }
         for (j = ftab[ss << 8] & CLEARMASK; j < copyStart[ss]; j++) {
            k = ptr[j]-1; if (k < 0) k += nblock;
            c1 = block[k];
            if (!bigDone[c1])
               ptr[ copyStart[c1]++ ] = k;
         }
         for (j = (ftab[(ss+1) << 8] & CLEARMASK) - 1; j > copyEnd[ss]; j--) {
            k = ptr[j]-1; if (k < 0) k += nblock;
            c1 = block[k];
            if (!bigDone[c1]) 
               ptr[ copyEnd[c1]-- ] = k;
         }
      }

      AssertH ( (copyStart[ss]-1 == copyEnd[ss])
                || 
                /* Extremely rare case missing in bzip2-1.0.0 and 1.0.1.
                   Necessity for this case is demonstrated by compressing 
                   a sequence of approximately 48.5 million of character 
                   251; 1.0.0/1.0.1 will then die here. */
                (copyStart[ss] == 0 && copyEnd[ss] == nblock-1),
                1007 )

      for (j = 0; j <= 255; j++) ftab[(j << 8) + ss] |= SETMASK;

      /*--
         Step 3:
         The [ss] big bucket is now done.  Record this fact,
         and update the quadrant descriptors.  Remember to
         update quadrants in the overshoot area too, if
         necessary.  The "if (i < 255)" test merely skips
         this updating for the last bucket processed, since
         updating for the last bucket is pointless.

         The quadrant array provides a way to incrementally
         cache sort orderings, as they appear, so as to 
         make subsequent comparisons in fullGtU() complete
         faster.  For repetitive blocks this makes a big
         difference (but not big enough to be able to avoid
         the fallback sorting mechanism, exponential radix sort).

         The precise meaning is: at all times:

            for 0 <= i < nblock and 0 <= j <= nblock

            if block[i] != block[j], 

               then the relative values of quadrant[i] and 
                    quadrant[j] are meaningless.

               else {
                  if quadrant[i] < quadrant[j]
                     then the string starting at i lexicographically
                     precedes the string starting at j

                  else if quadrant[i] > quadrant[j]
                     then the string starting at j lexicographically
                     precedes the string starting at i

                  else
                     the relative ordering of the strings starting
                     at i and j has not yet been determined.
               }
      --*/
      bigDone[ss] = True;

      if (i < 255) {
         Int32 bbStart  = ftab[ss << 8] & CLEARMASK;
         Int32 bbSize   = (ftab[(ss+1) << 8] & CLEARMASK) - bbStart;
         Int32 shifts   = 0;

         while ((bbSize >> shifts) > 65534) shifts++;

         for (j = bbSize-1; j >= 0; j--) {
            Int32 a2update     = ptr[bbStart + j];
            UInt16 qVal        = (UInt16)(j >> shifts);
            quadrant[a2update] = qVal;
            if (a2update < BZ_N_OVERSHOOT)
               quadrant[a2update + nblock] = qVal;
         }
         AssertH ( ((bbSize-1) >> shifts) <= 65535, 1002 );
      }

   }

   if (verb >= 4)
      VPrintf3 ( "        %d pointers, %d sorted, %d scanned\n",
                 nblock, numQSorted, nblock - numQSorted );
}
