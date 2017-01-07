#pragma once
#include "ofMain.h"

namespace CodeJutsu {
    namespace Ray{
        //   b
        //  / \
        // a   c
        //given 3d points a,b,c, get angle in b
        static float angleFromPoints(ofVec3f a, ofVec3f b, ofVec3f c){
            ofVec3f ba = ofVec3f(a.x-b.x, a.y-b.y, a.z-b.z);
            ofVec3f bc = ofVec3f(c.x-b.x, c.y-b.y, c.z-b.z);
            
            ba.normalize();
            bc.normalize();
            
            float dp = ba.dot(bc);
            return acos(dp);
        }
        
        //   n  r
        //   ^  '
        //   | /
        //___|/____
        //   o\
        //     \i
        //      '
        static ofVec3f reflect(ofVec3f incident, ofVec3f normal){
            return (incident - 2*incident.dot(normal) * normal);
        }
        
        //i  n  r
        //'  ^  '
        // \ | /
        //__\|/____
        //   p
        static ofVec3f reflect(ofVec3f beamOrigin, ofVec3f impactPoint, ofVec3f normal, float length=1.0){
            ofVec3f incident = beamOrigin - impactPoint;
            incident *= -1;
            incident.normalize();
            ofVec3f reflected = CodeJutsu::Ray::reflect(incident, normal);
            reflected *= length;
            reflected += impactPoint;
            return reflected;
        }
    }
}