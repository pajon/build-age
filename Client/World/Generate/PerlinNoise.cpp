//
//  PerlinNoise.cpp
//  GAME
//
//  Created by Patrik Štrba on 24.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "PerlinNoise.h"


PerlinNoise::PerlinNoise()
{
    persistence = 0;
    frequency = 0;
    amplitude  = 0;
    octaves = 0;
    randomseed = 0;
}

PerlinNoise::PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
    Set(_persistence,_frequency,_amplitude,_octaves,_randomseed);
}

void PerlinNoise::Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
    persistence = _persistence;
    frequency = _frequency;
    amplitude  = _amplitude;
    octaves = _octaves;
    randomseed = 2 + _randomseed * _randomseed;
}

double PerlinNoise::GetHeight(double x, double y)
{
    return amplitude * Total(x, y);
}

double PerlinNoise::GetData(double x, double y)
{
    //properties of one octave (changing each loop)
    double t = 0.0f;
    double _amplitude = 4.5;
    double freq = 1;
    
    for(int k = 0; k < octaves; k++)
    {
        t += GetValue(x * freq + randomseed, y * freq + randomseed) * _amplitude;
        _amplitude *= persistence;
        freq *= 2;
    }
    
    return t;
}

double PerlinNoise::Total(double i, double j)
{
    //properties of one octave (changing each loop)
    double t = 0.0f;
    double freq = frequency;
    double g = 1.0;
    
    for(int k = 0; k < octaves; k++)
    {
        t += GetValue(j * freq + randomseed, i * freq + randomseed) * g;
        g *= persistence;
        freq *= 2;
    }
    
    return t;
}

double PerlinNoise::GetValue(double x, double y)
{
    int Xint = (int)x;
    int Yint = (int)y;
    double Xfrac = x - Xint;
    double Yfrac = y - Yint;
    
    //noise values
    double v00 = Noise(Xint, Yint);
    double v01 = Noise(Xint, Yint+1);
    double v10 = Noise(Xint+1, Yint);
    double v11 = Noise(Xint+1, Yint+1);
    return biLinearInterpolation(v00,v10,v01,v11,Xfrac,Yfrac);
}

double PerlinNoise::Interpolate(double x, double y, double a)
{
    double negA = 1.0 - a;
    double negASqr = negA * negA;
    double fac1 = 3.0 * (negASqr) - 2.0 * (negASqr * negA);
    double aSqr = a * a;
    double fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);
    
    return x * fac1 + y * fac2; //add the weighted factors
}

double PerlinNoise::Noise(int x, int y)
{
    int n = x * 61 + y * 89;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}

double PerlinNoise::linearInterpolation(double x0, double x1, double t){
    return x0+(x1-x0)*t;
}

double PerlinNoise::biLinearInterpolation(double x0y0, double x1y0, double x0y1, double x1y1, double x, double y){
    double tx = x; // easeCurve(x);
    double ty = y; // easeCurve(y);
	/*double tx = x;
     double ty = y;*/
    double u = linearInterpolation(x0y0,x1y0,tx);
    double v = linearInterpolation(x0y1,x1y1,tx);
    return linearInterpolation(u,v,ty);
}