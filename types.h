#ifndef _TYPES_H
#define _TYPES_H

/*! ****************************************************************************
* .INCLUDES
********************************************************************************/

/*! ****************************************************************************
* .DEFINES[global]
********************************************************************************/
/* Platform Symbols  */
#define CPU_TYPE_8      8
#define CPU_TYPE_16     16
#define CPU_TYPE_32     32

#define MSB_FIRST       0
#define LSB_FIRST       1

#define HIGH_BYTE_FIRST 0
#define LOW_BYTE_FIRST  1


/* Bool constant */
#define True    (bool) ( 1 == 1 )    /* Boolean value for True  */
#define False   (bool) ( 1 == 0 )    /* Boolean value for False */

/* Integer-type constant */
#define Yes       1                  /* Integer-type value for Yes   */
#define No        0                  /* Integer-type value for No    */
#define On        1                  /*
