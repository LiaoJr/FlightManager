#include"list.h"


#ifndef FUNC_H

#define FUNC_H

int ShowMenu();

bool FlightInfo_Read(ManNode_t *manager);

void FlightInfo_Input(ManNode_t *manager);

void FlightInfo_Print(ManNode_t *manager);

void PrintNodeInfo(Node_t *NodeFind)

Node_t *SearchByNum(Node_t *Node, char *num);

Node_t *SearchByPrice(Node_t *Node, char *price)

Node_t *SearchByTime(Node_t *Node, char *time)

Node_t *SearchByStartPlace(Node_t *Node, char *startplace)

Node_t *SearchByDestiny(Node_t *Node, char *destiny)

Node_t *SearchByBoard(Node_t *Node, char *BoardNum)

void FlightInfo_Search(ManNode_t *manager);

void FlightInfo_Delete(ManNode_t *manager);

void FlightInfo_Sort(ManNode_t *manager);

bool FlightInfo_Save(ManNode_t *manager);

#endif
