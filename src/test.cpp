#include "Cube.h"
#include <assert.h>
#include <Arduino.h>

void testAllBlack(Cube cube) {
    // Test all black
    bool pattern[4] = {true, true, true, true};
    face_t face = cube.getTestFace(pattern);
    if (face != 5) {
      Serial.println("Error: testAllBlack failed");
    }
}

void testAllWhite(Cube cube) {
  // Test all black
  bool pattern[4] = {false, false, false, false};
  face_t face = cube.getTestFace(pattern);
  if (face != 0) {
    Serial.println("Error: testAllWhite failed");
  }
}


void testOneBlack(Cube cube) {
  // Test all black
  bool pattern[4] = {false, false, false, false};

  for (int i = 0; i < 4; i++) {
    pattern[i] = true;
    face_t face = cube.getTestFace(pattern);
    if (face != 1) {
      Serial.println("Error: testOneBlack failed");
    }
    pattern[i] = false;
  }
}

void testOneWhite(Cube cube) {
  // Test all black
  bool pattern[4] = {true, true, true, true};

  for (int i = 0; i < 4; i++) {
    pattern[i] = false;
    face_t face = cube.getTestFace(pattern);
    if (face != 4) {
      Serial.println("Error: testOneWhite failed");
    }
    pattern[i] = true;
  }
}

void testTwoAdjacentBlack(Cube cube) {
  // Test all black
  bool pattern0[4] = {true, true, false, false};
  bool pattern1[4] = {false, true, true, false};
  bool pattern2[4] = {false, false, true, true};
  bool pattern3[4] = {true, false, false, true};

  face_t face = cube.getTestFace(pattern0);
  if (face != 2) { 
    Serial.println("Error: testTwoAdjacentBlack 0 failed");
  }
  face = cube.getTestFace(pattern1);
  if (face != 2) { 
    Serial.println("Error: testTwoAdjacentBlack 1 failed");
  }
  face = cube.getTestFace(pattern2);
  if (face != 2) { 
    Serial.println("Error: testTwoAdjacentBlack 2 failed");
  }

  face = cube.getTestFace(pattern3);
  if (face != 2) { 
    Serial.println("Error: testTwoAdjacentBlack 3 failed");
  }
}

void testTwoDiagonalBlack(Cube cube) {
  // Test all black
  bool pattern0[4] = {true, false, true, false};
  bool pattern1[4] = {false, true, false, true};

  face_t face = cube.getTestFace(pattern0);
  if (face != 3) {
    Serial.println("Error: testTwoDiagonalBlack 0 failed");
    Serial.println(face);
  }
  face = cube.getTestFace(pattern1);
  if (face != 3) {
    Serial.println("Error: testTwoDiagonalBlack 1 failed");
    Serial.println(face);
  }
}

void testCube() {
    Cube cube;

    testAllBlack(cube);
    testOneBlack(cube);
    testOneWhite(cube);
    testTwoAdjacentBlack(cube);
    testTwoDiagonalBlack(cube);
    testAllWhite(cube);
}