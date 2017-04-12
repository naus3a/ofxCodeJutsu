#pragma once
#include "ofMain.h"

namespace ofxCodeJutsu {
	namespace Geometry {
		static int axisName2axisId(char an) {
			switch (an)
			{
			case 'x':
				return 0;
			case 'y':
				return 1;
			case 'z':
				return 2;
			default:
				return -1;
			}
		}

		static ofVec3f makeAxis(int axisId) {
			ofVec3f axis(0, 0, 0);
			axis[axisId] = 1;
			return axis;
		}
		
		static ofVec3f getTriangleNormal(ofVec3f p1, ofVec3f p2, ofVec3f p3) {
			ofVec3f u = p2 - p1;
			ofVec3f v = p3 - p1;
			ofVec3f n = u.cross(v);
			n.normalize();
			return n;
		}

		static void planeFromPtAndNormal(ofVec3f pt, ofVec3f n, float &a, float & b, float &c, float & d) {
			a = n.x;
			b = n.y;
			c = n.z;
			d = -pt.dot(n);
		}

		static void planeFromTriangle(ofVec3f p1, ofVec3f p2, ofVec3f p3, float &a, float & b, float &c, float & d) {
			ofVec3f n = ofxCodeJutsu::Geometry::getTriangleNormal(p1, p2, p3);
			ofxCodeJutsu::Geometry::planeFromPtAndNormal(p1, n, a, b, c, d);
		}

		static float getSignedPlaneDistance(ofVec3f pt, float a, float b, float c, float d) {
			return (a*pt.x+b*pt.y+c*pt.z+d);
		}
        
        static float getUnsignedPlaneDistance(ofVec3f pt, float a, float b, float c, float d){
            return abs(ofxCodeJutsu::Geometry::getSignedPlaneDistance(pt,a,b,c,d));
        }

		static bool isPointInFrontOfPlane(ofVec3f pt, float a, float b, float c, float d) {
			return (ofxCodeJutsu::Geometry::getSignedPlaneDistance(pt, a, b, c, d) > 0);
		}
        
        static ofVec3f middleOfSegment(ofVec3f p1, ofVec3f p2){
            ofVec3f p = p2 - p1;
            p/=2;
            p += p1;
            return p;
        }
        
        static ofVec3f pointInTriangle(ofVec3f p1, ofVec3f p2, ofVec3f p3){
            ofVec3f p = ofxCodeJutsu::Geometry::middleOfSegment(p1, p2);
            p = ofxCodeJutsu::Geometry::middleOfSegment(p, p3);
            return p;
        }
        
        static int segmentIntersection2D(ofVec2f start0, ofVec2f end0, ofVec2f start1, ofVec2f end1, ofVec2f & collisionPt){
            ofVec2f s02;
            ofVec2f s10;
            ofVec2f s32;
            float s_numer;
            float t_numer;
            float denom;
            float t;
            
            s10.x = end0.x-start0.x;
            s10.y = end0.y-start0.y;
            s32.x = end1.x-start1.x;
            s32.y = end1.y-start1.y;
            
            denom = s10.x*s32.y-s32.x*s10.y;
            if(denom==0){
                return 0; //collinear
            }
            bool denomPositive = denom>0;
            
            s02.x = start0.x-start1.x;
            s02.y = start0.y-start1.y;
            s_numer = s10.x*s02.y-s10.y*s02.x;
            if((s_numer<0)==denomPositive){
                return 0; //no collision
            }
            
            t_numer = s32.x*s02.y-s32.y*s02.x;
            if((t_numer<0)==denomPositive){
                return 0; //no collision
            }
            
            if(((s_numer>denom)==denomPositive)||((t_numer>denom)==denomPositive)){
                return 0; //no collision
            }
            
            t = t_numer/denom;
            collisionPt.x = start0.x+(t*s10.x);
            collisionPt.y = start0.y+(t*s10.y);
            return 1;
        }
	}
}