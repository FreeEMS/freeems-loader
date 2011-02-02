/*
 * FreeEMS_LoaderSREC.h
 *
 *  Created on: Nov 29, 2010
 *      Author: seank
 */

#ifndef FREEEMS_LOADERSREC_H_
#define FREEEMS_LOADERSREC_H_

#include <string>
#include "FreeEMS_LoaderParsing.h"
#include <stdio.h>
#include <memory>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <QObject>

using namespace std;

#define START_OF_ADDRESS_OFFSET  0x04 //the first character of our address in hex ascii
#define BITS_PER_BYTE           0x08 // bits in a byte
#define CHECKSUM_BYTE           0x01 // checksum is 1 byte
#define TWO_BYTES               0x02 // two in hex
#define ONE_BYTE                0x01 // one byte in hex
#define TYPE_ID_BYTES           0x02 // num of bytes in type header
#define ONE_KB                  0x0400 // one kilo byte
#define CH_PAIR_COUNT_BYTE      0x01
#define ASCII_PAIR              0x02

//enum BOOL {READONLY, READWRITE}

class FreeEMS_LoaderSREC {
public:
	FreeEMS_LoaderSREC(int type);
	FreeEMS_LoaderSREC();
	FreeEMS_LoaderSREC(char *input, int numBytes, int type, unsigned int recordAddress);
	virtual ~FreeEMS_LoaderSREC();
//	bool verifyFile(int *file);
	int fillRecord(std::vector<char> binaryChars);
	/*
	 * calculate a records checksum and compre it to the stored value.
	 */
	bool verifyRecord();
	int  getRecordAddress();
	char getNextByte();
	char getRecordType();
	void buildRecord();
	void printRecord();
	void createFromString(string* lineIn);
	std::string retRecordString();

	/*
	  These characters when paired and interpreted as a hexadecimal value display
	  the least significant byte of the ones complement of the sum of the byte values
	  represented by the pairs of characters making up the count, the address, and
	  the data fields.
	*/
	void calculateCheckSum();

	int  putNextByte(char byte);
	int  setRecordAddress(unsigned int address);
	int  setRecordAddress(char* address);
	int  setRecordType(int type);
	int  setTypeIndex(int type);
	void setNumPairsInRecord();
	void initVariables();
	int  retRecordSize();
	bool lineIsLoadable(string* line);

	bool recordIsNull;
	char recordPayload[ONE_KB];

	unsigned int payloadAddress;
	int recordPayloadBytes;
	char recordBytes[ONE_KB];

signals:
        void WOInfo(string text);

private:
	string record;


	char recordAddressChars[ONE_KB];
	char recordTypeIdChars[TWO_BYTES];
	char recordPayloadPairCountChars[TWO_BYTES];
	char recordCheckSumChars[TWO_BYTES];

	unsigned char recordChkSum;
	unsigned char recordLoadedChkSum;
	//char checksum;

	int charsInAddress;
	int recordIndex;

 	int typeIndex;
 	int numHexValues;

	bool writeAccess;
	bool recordStatus;
	bool addressIsSet;
	bool typeIsSet;
	bool numPairsSet;

};

#endif /* FREEEMS_LOADERSREC_H_ */
