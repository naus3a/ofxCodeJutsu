#pragma once
#include "ofMain.h"
#include "GeometryJutsu.h"

namespace ofxCodeJutsu {
	namespace Matrix {
		static ofVec3f rotMatrix2radEulerAngles(ofMatrix3x3 mat) {
			ofVec3f a;
			//a.x = atan2(mat[7], mat[8]);
			//a.y = atan2(-mat[6], sqrt((mat[7]*mat[7])+(mat[8]*mat[8])));
			//a.z = atan2(mat[3], mat[0]);
			float sy = sqrt(mat[0]*mat[0]+mat[3]*mat[3]);
			bool singular = sy < 1e-6;
			if (!singular) {
				a.x = atan2(mat[7], mat[8]);
				a.y = atan2(-mat[6], sy);
				a.z = atan2(mat[3], mat[0]);
			}
			else {
				a.x = atan2(-mat[5], mat[4]);
				a.y = atan2(-mat[6], sy);
				a.z = 0;
			}
			return a;
		}

		static ofVec3f rotMatrix2degEulerAngles(ofMatrix3x3 mat) {
			ofVec3f a = ofxCodeJutsu::Matrix::rotMatrix2radEulerAngles(mat);
			a.x = ofRadToDeg(a.x);
			a.y = ofRadToDeg(a.y);
			a.z = ofRadToDeg(a.z);
			return a;
		}

		static ofQuaternion rotMatrix2quaternion(ofMatrix3x3 mat) {
			float w = sqrt((1+mat[0]+mat[4]+mat[8])/2);
			float w4 = w * 4;
			float x = (mat[7]-mat[5])/w4;
			float y = (mat[2]-mat[6])/w4;
			float z = (mat[3]-mat[1])/w4;
			return ofQuaternion(x, y, z, w);
		}

		static void applyEulerAngles(ofVec3f ea, ofVec3f order, ofQuaternion & q) {
			q.zeroRotation();
			for (int i = 0; i < 3; i++) {
				q.makeRotate(ea[order[i]], ofxCodeJutsu::Geometry::makeAxis(order[i]));
			}
		}

		static void applyEulerAngles(ofVec3f ea, char axis1st, char axis2nd, char axis3rd, ofQuaternion & q) {
			ofVec3f order;
			order[0] = ofxCodeJutsu::Geometry::axisName2axisId(axis1st);
			order[1] = ofxCodeJutsu::Geometry::axisName2axisId(axis2nd);
			order[2] = ofxCodeJutsu::Geometry::axisName2axisId(axis3rd);
			ofxCodeJutsu::Matrix::applyEulerAngles(ea, order, q);
		}
	}
};