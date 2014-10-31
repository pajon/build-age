//
//  PerlinNoise.h
//  GAME
//
//  Created by Patrik Štrba on 24.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__PerlinNoise__
#define __GAME__PerlinNoise__

#include <iostream>

class PerlinNoise
{
public:
    
    // Constructor
    PerlinNoise();
    PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    
    
    double linearInterpolation(double x0, double x1, double t);
    double biLinearInterpolation(double x0y0, double x1y0, double x0y1, double x1y1, double x, double y);
    
    // Get Height
    double GetHeight(double x, double y);
    double GetData(double x, double y);
    
    // Get
    double Persistence() const { return persistence; }
    double Frequency()   const { return frequency;   }
    double Amplitude()   const { return amplitude;   }
    int    Octaves()     const { return octaves;     }
    int    RandomSeed()  const { return randomseed;  }
    
    // Set
    void Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
    
    void SetPersistence(double _persistence) { persistence = _persistence; }
    void SetFrequency(  double _frequency)   { frequency = _frequency;     }
    void SetAmplitude(  double _amplitude)   { amplitude = _amplitude;     }
    void SetOctaves(    int    _octaves)     { octaves = _octaves;         }
    void SetRandomSeed( int    _randomseed)  { randomseed = _randomseed;   }
    
private:
    
    double Total(double i, double j);
    double GetValue(double x, double y);
    double Interpolate(double x, double y, double a);
    double Noise(int x, int y);
    
    double persistence, frequency, amplitude;
    int octaves, randomseed;
};

#endif /* defined(__GAME__PerlinNoise__) */
