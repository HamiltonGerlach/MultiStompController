#ifndef PARAMMAP_H
#define PARAMMAP_H

#define PARAM_LENGTH_P0 12
#define PARAM_LENGTH_P1 11
#define PARAM_LENGTH_P2 11
#define PARAM_LENGTH_P3 8
#define PARAM_LENGTH_P4 8
#define PARAM_LENGTH_P5 8
#define PARAM_LENGTH_P6 8
#define PARAM_LENGTH_P7 9
#define PARAM_LENGTH_P8 8
#define PARAM_LENGTH_MAX 12

#define PARAM_NUM 9

// Patch parameter map:
//  [Effect]        ... 0 - 5
//  [Param]         ... 0 - 8
//  [Bit of value]  ... 0 - 11
//  [Offset/Index]  ... 0 (Offset), 1 (Bit index)

// Access via pgm_read_byte_near(&ParamMap[i][j][k][l])

byte ParamLength[PARAM_NUM] = { PARAM_LENGTH_P0,
                                PARAM_LENGTH_P1,
                                PARAM_LENGTH_P2,
                                PARAM_LENGTH_P3,                                
                                PARAM_LENGTH_P4,
                                PARAM_LENGTH_P5,
                                PARAM_LENGTH_P6,
                                PARAM_LENGTH_P7,
                                PARAM_LENGTH_P8 };

const PROGMEM byte ParamMap[ZOOM_EFF_NO][PARAM_NUM][PARAM_LENGTH_MAX][2] =
{
    { // EFFECT 0
        {   // EFFECT 0 PARAMETER 0
            { 9  , 5 },
            { 9  , 6 },
            { 5  , 3 },
            { 10 , 0 },
            { 10 , 1 },
            { 10 , 2 },
            { 10 , 3 },
            { 10 , 4 },
            { 10 , 5 },
            { 10 , 6 },
            { 5  , 2 },
            { 11 , 0 }
        }, 
        
        {   // EFFECT 0 PARAMETER 1
            { 11 , 2 },
            { 11 , 3 },
            { 11 , 4 },
            { 11 , 5 },
            { 11 , 6 },
            { 5  , 1 },
            { 12 , 0 },
            { 12 , 1 },
            { 12 , 2 },
            { 12 , 3 },
            { 12 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 2
            { 5  , 0 },
            { 14 , 0 },
            { 14 , 1 },
            { 14 , 2 },
            { 14 , 3 },
            { 14 , 4 },
            { 14 , 5 },
            { 14 , 6 },
            { 13 , 6 },
            { 15 , 0 },
            { 15 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 3
            { 15 , 4 },
            { 15 , 5 },
            { 15 , 6 },
            { 13 , 5 },
            { 16 , 0 },
            { 16 , 1 },
            { 16 , 2 },
            { 16 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 4
            { 16 , 4 },
            { 16 , 5 },
            { 16 , 6 },
            { 13 , 4 },
            { 17 , 0 },
            { 17 , 1 },
            { 17 , 2 },
            { 17 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 5
            { 17 , 4 },
            { 17 , 5 },
            { 17 , 6 },
            { 13 , 3 },
            { 18 , 0 },
            { 18 , 1 },
            { 18 , 2 },
            { 18 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 6
            { 18 , 4 },
            { 18 , 5 },
            { 18 , 6 },
            { 13 , 2 },
            { 19 , 0 },
            { 19 , 1 },
            { 19 , 2 },
            { 19 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 7
            { 19 , 4 },
            { 19 , 5 },
            { 19 , 6 },
            { 13 , 1 },
            { 20 , 0 },
            { 20 , 1 },
            { 20 , 2 },
            { 20 , 3 },
            { 20 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 0 PARAMETER 8
            { 24 , 0 },
            { 24 , 1 },
            { 24 , 2 },
            { 24 , 3 },
            { 24 , 4 },
            { 24 , 5 },
            { 24 , 6 },
            { 21 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    },
    ///////////////////////////////
    
    { // EFFECT 1
        {   // EFFECT 1 PARAMETER 0
            { 30 , 5 },
            { 30 , 6 },
            { 29 , 6 },
            { 31 , 0 },
            { 31 , 1 },
            { 31 , 2 },
            { 31 , 3 },
            { 31 , 4 },
            { 31 , 5 },
            { 31 , 6 },
            { 29 , 5 },
            { 32 , 0 }
        }, 
        
        {   // EFFECT 1 PARAMETER 1
            { 32 , 2 },
            { 32 , 3 },
            { 32 , 4 },
            { 32 , 5 },
            { 32 , 6 },
            { 29 , 4 },
            { 33 , 0 },
            { 33 , 1 },
            { 33 , 2 },
            { 33 , 3 },
            { 33 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 2
            { 29 , 3 },
            { 34 , 0 },
            { 34 , 1 },
            { 34 , 2 },
            { 34 , 3 },
            { 34 , 4 },
            { 34 , 5 },
            { 34 , 6 },
            { 29 , 2 },
            { 35 , 0 },
            { 35 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 3
            { 35 , 4 },
            { 35 , 5 },
            { 35 , 6 },
            { 29 , 1 },
            { 36 , 0 },
            { 36 , 1 },
            { 36 , 2 },
            { 36 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 4
            { 36 , 4 },
            { 36 , 5 },
            { 36 , 6 },
            { 29 , 0 },
            { 38 , 0 },
            { 38 , 1 },
            { 38 , 2 },
            { 38 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 5
            { 38 , 4 },
            { 38 , 5 },
            { 38 , 6 },
            { 37 , 6 },
            { 39 , 0 },
            { 39 , 1 },
            { 39 , 2 },
            { 39 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 6
            { 39 , 4 },
            { 39 , 5 },
            { 39 , 6 },
            { 37 , 5 },
            { 40 , 0 },
            { 40 , 1 },
            { 40 , 2 },
            { 40 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 7
            { 40 , 4 },
            { 40 , 5 },
            { 40 , 6 },
            { 37 , 4 },
            { 41 , 0 },
            { 41 , 1 },
            { 41 , 2 },
            { 41 , 3 },
            { 41 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 1 PARAMETER 8
            { 44 , 0 },
            { 44 , 1 },
            { 44 , 2 },
            { 44 , 3 },
            { 44 , 4 },
            { 44 , 5 },
            { 44 , 6 },
            { 37 , 0 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    },
    ///////////////////////////////
    
    { // EFFECT 2
        {   // EFFECT 2 PARAMETER 0
            { 50 , 5 },
            { 50 , 6 },
            { 45 , 2 },
            { 51 , 0 },
            { 51 , 1 },
            { 51 , 2 },
            { 51 , 3 },
            { 51 , 4 },
            { 51 , 5 },
            { 51 , 6 },
            { 45 , 1 },
            { 52 , 0 }
        }, 
        
        {   // EFFECT 2 PARAMETER 1
            { 52 , 2 },
            { 52 , 3 },
            { 52 , 4 },
            { 52 , 5 },
            { 52 , 6 },
            { 45 , 0 },
            { 54 , 0 },
            { 54 , 1 },
            { 54 , 2 },
            { 54 , 3 },
            { 54 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 2
            { 53 , 6 },
            { 55 , 0 },
            { 55 , 1 },
            { 55 , 2 },
            { 55 , 3 },
            { 55 , 4 },
            { 55 , 5 },
            { 55 , 6 },
            { 53 , 5 },
            { 56 , 0 },
            { 56 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 3
            { 56 , 4 },
            { 56 , 5 },
            { 56 , 6 },
            { 53 , 4 },
            { 57 , 0 },
            { 57 , 1 },
            { 57 , 2 },
            { 57 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 4
            { 57 , 4 },
            { 57 , 5 },
            { 57 , 6 },
            { 53 , 3 },
            { 58 , 0 },
            { 58 , 1 },
            { 58 , 2 },
            { 58 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 5
            { 58 , 4 },
            { 58 , 5 },
            { 58 , 6 },
            { 53 , 2 },
            { 59 , 0 },
            { 59 , 1 },
            { 59 , 2 },
            { 59 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 6
            { 59 , 4 },
            { 59 , 5 },
            { 59 , 6 },
            { 53 , 1 },
            { 60 , 0 },
            { 60 , 1 },
            { 60 , 2 },
            { 60 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 7
            { 60 , 4 },
            { 60 , 5 },
            { 60 , 6 },
            { 53 , 0 },
            { 62 , 0 },
            { 62 , 1 },
            { 62 , 2 },
            { 62 , 3 },
            { 62 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 2 PARAMETER 8
            { 65 , 0 },
            { 65 , 1 },
            { 65 , 2 },
            { 65 , 3 },
            { 65 , 4 },
            { 65 , 5 },
            { 65 , 6 },
            { 61 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    },
    ///////////////////////////////
    
    { // EFFECT 3
        {   // EFFECT 3 PARAMETER 0
            { 71 , 5 },
            { 71 , 6 },
            { 69 , 5 },
            { 72 , 0 },
            { 72 , 1 },
            { 72 , 2 },
            { 72 , 3 },
            { 72 , 4 },
            { 72 , 5 },
            { 72 , 6 },
            { 69 , 4 },
            { 73 , 0 }
        }, 
        
        {   // EFFECT 3 PARAMETER 1
            { 73 , 2 },
            { 73 , 3 },
            { 73 , 4 },
            { 73 , 5 },
            { 73 , 6 },
            { 69 , 3 },
            { 74 , 0 },
            { 74 , 1 },
            { 74 , 2 },
            { 74 , 3 },
            { 74 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 2
            { 69 , 2 },
            { 75 , 0 },
            { 75 , 1 },
            { 75 , 2 },
            { 75 , 3 },
            { 75 , 4 },
            { 75 , 5 },
            { 75 , 6 },
            { 69 , 1 },
            { 76 , 0 },
            { 76 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 3
            { 76 , 4 },
            { 76 , 5 },
            { 76 , 6 },
            { 69 , 0 },
            { 78 , 0 },
            { 78 , 1 },
            { 78 , 2 },
            { 78 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 4
            { 78 , 4 },
            { 78 , 5 },
            { 78 , 6 },
            { 77 , 6 },
            { 79 , 0 },
            { 79 , 1 },
            { 79 , 2 },
            { 79 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 5
            { 79 , 4 },
            { 79 , 5 },
            { 79 , 6 },
            { 77 , 5 },
            { 80 , 0 },
            { 80 , 1 },
            { 80 , 2 },
            { 80 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 6
            { 80 , 4 },
            { 80 , 5 },
            { 80 , 6 },
            { 77 , 4 },
            { 81 , 0 },
            { 81 , 1 },
            { 81 , 2 },
            { 81 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 7
            { 81 , 4 },
            { 81 , 5 },
            { 81 , 6 },
            { 77 , 3 },
            { 82 , 0 },
            { 82 , 1 },
            { 82 , 2 },
            { 82 , 3 },
            { 82 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 3 PARAMETER 8
            { 86 , 0 },
            { 86 , 1 },
            { 86 , 2 },
            { 86 , 3 },
            { 86 , 4 },
            { 86 , 5 },
            { 86 , 6 },
            { 85 , 6 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    },
    ///////////////////////////////
    
    { // EFFECT 4
        {   // EFFECT 4 PARAMETER 0
            { 91 , 5 },
            { 91 , 6 },
            { 85 , 1 },
            { 92 , 0 },
            { 92 , 1 },
            { 92 , 2 },
            { 92 , 3 },
            { 92 , 4 },
            { 92 , 5 },
            { 92 , 6 },
            { 85 , 0 },
            { 94 , 0 }
        }, 
        
        {   // EFFECT 4 PARAMETER 1
            { 94 , 2 },
            { 94 , 3 },
            { 94 , 4 },
            { 94 , 5 },
            { 94 , 6 },
            { 93 , 6 },
            { 95 , 0 },
            { 95 , 1 },
            { 95 , 2 },
            { 95 , 3 },
            { 95 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 2
            { 93 , 5 },
            { 96 , 0 },
            { 96 , 1 },
            { 96 , 2 },
            { 96 , 3 },
            { 96 , 4 },
            { 96 , 5 },
            { 96 , 6 },
            { 93 , 4 },
            { 97 , 0 },
            { 97 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 3
            { 97 , 4 },
            { 97 , 5 },
            { 97 , 6 },
            { 93 , 3 },
            { 98 , 0 },
            { 98 , 1 },
            { 98 , 2 },
            { 98 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 4
            { 98 , 4 },
            { 98 , 5 },
            { 98 , 6 },
            { 93 , 2 },
            { 99 , 0 },
            { 99 , 1 },
            { 99 , 2 },
            { 99 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 5
            { 99  , 4 },
            { 99  , 5 },
            { 99  , 6 },
            { 93  , 1 },
            { 100 , 0 },
            { 100 , 1 },
            { 100 , 2 },
            { 100 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 6
            { 100 , 4 },
            { 100 , 5 },
            { 100 , 6 },
            { 93  , 0 },
            { 102 , 0 },
            { 102 , 1 },
            { 102 , 2 },
            { 102 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 7
            { 102 , 4 },
            { 102 , 5 },
            { 102 , 6 },
            { 101 , 6 },
            { 103 , 0 },
            { 103 , 1 },
            { 103 , 2 },
            { 103 , 3 },
            { 103 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 4 PARAMETER 8
            { 106 , 0 },
            { 106 , 1 },
            { 106 , 2 },
            { 106 , 3 },
            { 106 , 4 },
            { 106 , 5 },
            { 106 , 6 },
            { 101 , 2 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    },
    ///////////////////////////////
    
    { // EFFECT 5
        {   // EFFECT 5 PARAMETER 0
            { 112 , 5 },
            { 112 , 6 },
            { 109 , 4 },
            { 113 , 0 },
            { 113 , 1 },
            { 113 , 2 },
            { 113 , 3 },
            { 113 , 4 },
            { 113 , 5 },
            { 113 , 6 },
            { 109 , 3 },
            { 114 , 0 }
        }, 
        
        {   // EFFECT 5 PARAMETER 1
            { 114 , 2 },
            { 114 , 3 },
            { 114 , 4 },
            { 114 , 5 },
            { 114 , 6 },
            { 109 , 2 },
            { 116 , 0 },
            { 116 , 1 },
            { 116 , 2 },
            { 116 , 3 },
            { 116 , 4 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 2
            { 109 , 1 },
            { 116 , 0 },
            { 116 , 1 },
            { 116 , 2 },
            { 116 , 3 },
            { 116 , 4 },
            { 116 , 5 },
            { 116 , 6 },
            { 109 , 0 },
            { 118 , 0 },
            { 118 , 1 },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 3
            { 118 , 4 },
            { 118 , 5 },
            { 118 , 6 },
            { 117 , 6 },
            { 119 , 0 },
            { 119 , 1 },
            { 119 , 2 },
            { 119 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 4
            { 119 , 4 },
            { 119 , 5 },
            { 119 , 6 },
            { 117 , 5 },
            { 120 , 0 },
            { 120 , 1 },
            { 120 , 2 },
            { 120 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 5
            { 120 , 4 },
            { 120 , 5 },
            { 120 , 6 },
            { 117 , 4 },
            { 121 , 0 },
            { 121 , 1 },
            { 121 , 2 },
            { 121 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 6
            { 121 , 4 },
            { 121 , 5 },
            { 121 , 6 },
            { 117 , 3 },
            { 122 , 0 },
            { 122 , 1 },
            { 122 , 2 },
            { 122 , 3 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 7
            { 122 , 4 },
            { 122 , 5 },
            { 122 , 6 },
            { 117 , 2 },
            { 123 , 0 },
            { 123 , 1 },
            { 123 , 2 },
            { 123 , 3 },
            { 123 , 4 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        },
        
        {   // EFFECT 5 PARAMETER 8
            { 127 , 0 },
            { 127 , 1 },
            { 127 , 2 },
            { 127 , 3 },
            { 127 , 4 },
            { 127 , 5 },
            { 127 , 6 },
            { 125 , 5 },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF },
            { 0xFF, 0xFF }
        }
    }
};

#endif

// --------------------------
// 
// Effect 0
// 
// Param 0 
// 
// b0      9       5
// b1      9       6
// b2      5       3
// b3      10      0
// b4      10      1
// b5      10      2
// b6      10      3
// b7      10      4
// b8      10      5
// b9      10      6
// b10     5       2
// b11     11      0
// 
// Param 1
// 
// b0      11      2
// b1      11      3
// b2      11      4
// b3      11      5
// b4      11      6
// b5      5       1
// b6      12      0
// b7      12      1
// b8      12      2
// b9      12      3
// b10     12      4
// 
// Param 2
// 
// b0      5       0
// b1      14      0
// b2      14      1
// b3      14      2
// b4      14      3
// b5      14      4
// b6      14      5
// b7      14      6
// b8      13      6
// b9      15      0
// b10     15      1
// 
// Param 3
// 
// b0      15      4
// b1      15      5
// b2      15      6
// b3      13      5
// b4      16      0
// b5      16      1
// b6      16      2
// b7      16      3
// 
// Param 4
// 
// b0      16      4
// b1      16      5
// b2      16      6
// b3      13      4
// b4      17      0
// b5      17      1
// b6      17      2
// b7      17      3
// 
// Param 5
// 
// b0      17      4
// b1      17      5
// b2      17      6
// b3      13      3
// b4      18      0
// b5      18      1
// b6      18      2
// b7      18      3
// 
// Param 6
// 
// b0      18      4
// b1      18      5
// b2      18      6
// b3      13      2
// b4      19      0
// b5      19      1
// b6      19      2
// b7      19      3
// 
// Param 7
// 
// b0      19      4
// b1      19      5
// b2      19      6
// b3      13      1
// b4      20      0
// b5      20      1
// b6      20      2
// b7      20      3
// b8      20      4
// 
// Param 8
// 
// b0      24      0
// b1      24      1
// b2      24      2
// b3      24      3
// b4      24      4
// b5      24      5
// b6      24      6
// b7      21      4
// 
// -------------------------------
// 
// Effect 1
// 
// Param 0 
// 
// b0      30      5
// b1      30      6
// b2      29      6
// b3      31      0
// b4      31      1
// b5      31      2
// b6      31      3
// b7      31      4
// b8      31      5
// b9      31      6
// b10     29      5
// b11     32      0
// 
// Param 1
// 
// b0      32      2
// b1      32      3
// b2      32      4
// b3      32      5
// b4      32      6
// b5      29      4
// b6      33      0
// b7      33      1
// b8      33      2
// b9      33      3
// b10     33      4
// 
// Param 2
// 
// b0      29      3
// b1      34      0
// b2      34      1
// b3      34      2
// b4      34      3
// b5      34      4
// b6      34      5
// b7      34      6
// b8      29      2
// b9      35      0
// b10     35      1
// 
// Param 3
// 
// b0      35      4
// b1      35      5
// b2      35      6
// b3      29      1
// b4      36      0
// b5      36      1
// b6      36      2
// b7      36      3
// 
// Param 4
// 
// b0      36      4
// b1      36      5
// b2      36      6
// b3      29      0
// b4      38      0
// b5      38      1
// b6      38      2
// b7      38      3
// 
// Param 5
// 
// b0      38      4
// b1      38      5
// b2      38      6
// b3      37      6
// b4      39      0
// b5      39      1
// b6      39      2
// b7      39      3
// 
// Param 6
// 
// b0      39      4
// b1      39      5
// b2      39      6
// b3      37      5
// b4      40      0
// b5      40      1
// b6      40      2
// b7      40      3
// 
// Param 7
// 
// b0      40      4
// b1      40      5
// b2      40      6
// b3      37      4
// b4      41      0
// b5      41      1
// b6      41      2
// b7      41      3
// b8      41      4
// 
// Param 8
// 
// b0      44      0
// b1      44      1
// b2      44      2
// b3      44      3
// b4      44      4
// b5      44      5
// b6      44      6
// b7      37      0
// 
// -------------------------------
// 
// Effect 2
// 
// Param 0 
// 
// b0      50      5
// b1      50      6
// b2      45      2
// b3      51      0
// b4      51      1
// b5      51      2
// b6      51      3
// b7      51      4
// b8      51      5
// b9      51      6
// b10     45      1
// b11     52      0
// 
// Param 1
// 
// b0      52      2
// b1      52      3
// b2      52      4
// b3      52      5
// b4      52      6
// b5      45      0
// b6      54      0
// b7      54      1
// b8      54      2
// b9      54      3
// b10     54      4
// 
// Param 2
// 
// b0      53      6
// b1      55      0
// b2      55      1
// b3      55      2
// b4      55      3
// b5      55      4
// b6      55      5
// b7      55      6
// b8      53      5
// b9      56      0
// b10     56      1
// 
// Param 3
// 
// b0      56      4
// b1      56      5
// b2      56      6
// b3      53      4
// b4      57      0
// b5      57      1
// b6      57      2
// b7      57      3
// 
// Param 4
// 
// b0      57      4
// b1      57      5
// b2      57      6
// b3      53      3
// b4      58      0
// b5      58      1
// b6      58      2
// b7      58      3
// 
// Param 5
// 
// b0      58      4
// b1      58      5
// b2      58      6
// b3      53      2
// b4      59      0
// b5      59      1
// b6      59      2
// b7      59      3
// 
// Param 6
// 
// b0      59      4
// b1      59      5
// b2      59      6
// b3      53      1
// b4      60      0
// b5      60      1
// b6      60      2
// b7      60      3
// 
// Param 7
// 
// b0      60      4
// b1      60      5
// b2      60      6
// b3      53      0
// b4      62      0
// b5      62      1
// b6      62      2
// b7      62      3
// b8      62      4
// 
// Param 8
// 
// b0      65      0
// b1      65      1
// b2      65      2
// b3      65      3
// b4      65      4
// b5      65      5
// b6      65      6
// b7      61      3
// 
// -------------------------------
// 
// Effect 3
// 
// Param 0 
// 
// b0      71      5
// b1      71      6
// b2      69      5
// b3      72      0
// b4      72      1
// b5      72      2
// b6      72      3
// b7      72      4
// b8      72      5
// b9      72      6
// b10     69      4
// b11     73      0
// 
// Param 1
// 
// b0      73      2
// b1      73      3
// b2      73      4
// b3      73      5
// b4      73      6
// b5      69      3
// b6      74      0
// b7      74      1
// b8      74      2
// b9      74      3
// b10     74      4
// 
// Param 2
// 
// b0      69      2
// b1      75      0
// b2      75      1
// b3      75      2
// b4      75      3
// b5      75      4
// b6      75      5
// b7      75      6
// b8      69      1
// b9      76      0
// b10     76      1
// 
// Param 3
// 
// b0      76      4
// b1      76      5
// b2      76      6
// b3      69      0
// b4      78      0
// b5      78      1
// b6      78      2
// b7      78      3
// 
// Param 4
// 
// b0      78      4
// b1      78      5
// b2      78      6
// b3      77      6
// b4      79      0
// b5      79      1
// b6      79      2
// b7      79      3
// 
// Param 5
// 
// b0      79      4
// b1      79      5
// b2      79      6
// b3      77      5
// b4      80      0
// b5      80      1
// b6      80      2
// b7      80      3
// 
// Param 6
// 
// b0      80      4
// b1      80      5
// b2      80      6
// b3      77      4
// b4      81      0
// b5      81      1
// b6      81      2
// b7      81      3
// 
// Param 7
// 
// b0      81      4
// b1      81      5
// b2      81      6
// b3      77      3
// b4      82      0
// b5      82      1
// b6      82      2
// b7      82      3
// b8      82      4
// 
// Param 8
// 
// b0      86      0
// b1      86      1
// b2      86      2
// b3      86      3
// b4      86      4
// b5      86      5
// b6      86      6
// b7      85      6
// 
// -------------------------------
// 
// Effect 4
// 
// Param 0 
// 
// b0      91      5
// b1      91      6
// b2      85      1
// b3      92      0
// b4      92      1
// b5      92      2
// b6      92      3
// b7      92      4
// b8      92      5
// b9      92      6
// b10     85      0
// b11     94      0
// 
// Param 1
// 
// b0      94      2
// b1      94      3
// b2      94      4
// b3      94      5
// b4      94      6
// b5      93      6
// b6      95      0
// b7      95      1
// b8      95      2
// b9      95      3
// b10     95      4
// 
// Param 2
// 
// b0      93      5
// b1      96      0
// b2      96      1
// b3      96      2
// b4      96      3
// b5      96      4
// b6      96      5
// b7      96      6
// b8      93      4
// b9      97      0
// b10     97      1
// 
// Param 3
// 
// b0      97      4
// b1      97      5
// b2      97      6
// b3      93      3
// b4      98      0
// b5      98      1
// b6      98      2
// b7      98      3
// 
// Param 4
// 
// b0      98      4
// b1      98      5
// b2      98      6
// b3      93      2
// b4      99      0
// b5      99      1
// b6      99      2
// b7      99      3
// 
// Param 5
// 
// b0      99      4
// b1      99      5
// b2      99      6
// b3      93      1
// b4      100     0
// b5      100     1
// b6      100     2
// b7      100     3
// 
// Param 6
// 
// b0      100     4
// b1      100     5
// b2      100     6
// b3      93      0
// b4      102     0
// b5      102     1
// b6      102     2
// b7      102     3
// 
// Param 7
// 
// b0      102     4
// b1      102     5
// b2      102     6
// b3      101     6
// b4      103     0
// b5      103     1
// b6      103     2
// b7      103     3
// b8      103     4
// 
// Param 8
// 
// b0      106     0
// b1      106     1
// b2      106     2
// b3      106     3
// b4      106     4
// b5      106     5
// b6      106     6
// b7      101     2
// 
// -------------------------------
// 
// Effect 5
// 
// Param 0 
// 
// b0      112     5
// b1      112     6
// b2      109     4
// b3      113     0
// b4      113     1
// b5      113     2
// b6      113     3
// b7      113     4
// b8      113     5
// b9      113     6
// b10     109     3
// b11     114     0
// 
// Param 1
// 
// b0      114     2
// b1      114     3
// b2      114     4
// b3      114     5
// b4      114     6
// b5      109     2
// b6      116     0
// b7      116     1
// b8      116     2
// b9      116     3
// b10     116     4
// 
// Param 2
// 
// b0      109     1
// b1      116     0
// b2      116     1
// b3      116     2
// b4      116     3
// b5      116     4
// b6      116     5
// b7      116     6
// b8      109     0
// b9      118     0
// b10     118     1
// 
// Param 3
// 
// b0      118     4
// b1      118     5
// b2      118     6
// b3      117     6
// b4      119     0
// b5      119     1
// b6      119     2
// b7      119     3
// 
// Param 4
// 
// b0      119     4
// b1      119     5
// b2      119     6
// b3      117     5
// b4      120     0
// b5      120     1
// b6      120     2
// b7      120     3
// 
// Param 5
// 
// b0      120     4
// b1      120     5
// b2      120     6
// b3      117     4
// b4      121     0
// b5      121     1
// b6      121     2
// b7      121     3
// 
// Param 6
// 
// b0      121     4
// b1      121     5
// b2      121     6
// b3      117     3
// b4      122     0
// b5      122     1
// b6      122     2
// b7      122     3
// 
// Param 7
// 
// b0      122     4
// b1      122     5
// b2      122     6
// b3      117     2
// b4      123     0
// b5      123     1
// b6      123     2
// b7      123     3
// b8      123     4
// 
// Param 8
// 
// b0      127     0
// b1      127     1
// b2      127     2
// b3      127     3
// b4      127     4
// b5      127     5
// b6      127     6
// b7      125     5