#include "web.h"

extern std::map<String, String> inputMap;
extern std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
extern std::array<std::map<String, String>, MAX_CHANNELS> outputsMap;

String inputProcessor(const String& var){
  //Serial.println("processing: " + var);
  if (inputMap.count(var.c_str()) > 0) {
    return inputMap[var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String level1Processor(const String& var){
  //Serial.println("processing: " + var);
  if (levelsMap[0].count(var.c_str()) > 0) {
    return levelsMap[0][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String level2Processor(const String& var){
  //Serial.println("processing: " + var);
  if (levelsMap[1].count(var.c_str()) > 0) {
    return levelsMap[1][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String level3Processor(const String& var){
  //Serial.println("processing: " + var);
  if (levelsMap[2].count(var.c_str()) > 0) {
    return levelsMap[2][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out1Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[0].count(var.c_str()) > 0) {
    return outputsMap[0][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out2Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[1].count(var.c_str()) > 0) {
    return outputsMap[1][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out3Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[2].count(var.c_str()) > 0) {
    return outputsMap[2][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out4Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[3].count(var.c_str()) > 0) {
    return outputsMap[3][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out5Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[4].count(var.c_str()) > 0) {
    return outputsMap[4][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out6Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[5].count(var.c_str()) > 0) {
    return outputsMap[5][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out7Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[6].count(var.c_str()) > 0) {
    return outputsMap[6][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out8Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[7].count(var.c_str()) > 0) {
    return outputsMap[7][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out9Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[8].count(var.c_str()) > 0) {
    return outputsMap[8][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out10Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[9].count(var.c_str()) > 0) {
    return outputsMap[9][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out11Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[10].count(var.c_str()) > 0) {
    return outputsMap[10][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String out12Processor(const String& var){
  //Serial.println("processing: " + var);
  if (outputsMap[11].count(var.c_str()) > 0) {
    return outputsMap[11][var.c_str()];
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}