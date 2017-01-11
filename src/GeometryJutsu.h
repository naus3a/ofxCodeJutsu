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

		static bool isPointInFrontOfPlane(ofVec3f pt, float a, float b, float c, float d) {
			return (ofxCodeJutsu::Geometry::getSignedPlaneDistance(pt, a, b, c, d) > 0);
		}

	}
}