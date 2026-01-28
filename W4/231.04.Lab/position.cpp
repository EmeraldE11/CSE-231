/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Noah McCarthy
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>

double Position::squareWidth = SIZE_SQUARE;
double Position::squareHeight = SIZE_SQUARE;

/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream& operator << (ostream& out, const Position& rhs)
{
	if (!rhs.isValid())
		out << "--";
	else
		out << char('a' + rhs.getCol())
		<< char('1' + rhs.getRow());
	return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator >> (istream& in, Position& rhs)
{
	string s;
	in >> s;
	rhs = s;
	return in;
}


/*DEFAULT CONSTRUCTOR*/
Position::Position()
{
	setInvalid();
}

/*COPY CONSTRUCTOR*/
Position::Position(const Position& rhs)
{
	colRow = rhs.colRow;
}


/*VALIDITY*/
bool Position::isValid()   const { return (colRow & 0x88) == 0; }
bool Position::isInvalid() const { return !isValid(); }
void Position::setValid() {
	if (isInvalid())
		colRow = 0x00;
}
void Position::setInvalid() { colRow = 0xff; }

/*COMPARISON*/
bool Position::operator < (const Position& rhs) const {
	return colRow < rhs.colRow;
}
bool Position::operator == (const Position& rhs) const {
	return colRow == rhs.colRow;
}
bool Position::operator != (const Position& rhs) const {
	return !(*this == rhs);
}
const Position& Position::operator = (const Position& rhs) {
	colRow = rhs.colRow;
	return *this;
}

/*LOCATION*/
Position::Position(int location) {
	setLocation(location);
}
int Position::getLocation() const {
	if (!isValid())
		return -1;
	return (getRow() * 8) + getCol();
}
void Position::setLocation(int location) {
	if (location < 0 || location >= 64) {
		setInvalid();
		return;
	}
	int r = location / 8;
	int c = location % 8;
	set(c, r);
}

/*ROW/COL*/
Position::Position(int c, int r) {
	set(c, r);
}
int Position::getCol() const {
	return isValid() ? ((colRow >> 4) & 0x0f) : -1;
}
int Position::getRow() const {
	return isValid() ? (colRow & 0x0f) : -1;
}
void Position::setRow(int r) {
	if (!isValid() || r < 0 || r > 7)
		setInvalid();
	else
		colRow = (colRow & 0xf0) | r;
}
void Position::setCol(int c) {
	if (!isValid() || c < 0 || c > 7)
		setInvalid();
	else
		colRow = (c << 4) | (colRow & 0x0f);
}
void Position::set(int c, int r) {
	if (c < 0 || c > 7 || r < 0 || r > 7)
		setInvalid();
	else
		colRow = (c << 4) | r;
}

/*TEXT*/
Position::Position(const char* s) {
	*this = s;
}
const Position& Position::operator = (const char* rhs) {
	if (!rhs || rhs[0] < 'a' || rhs[0] > 'h' ||
		rhs[1] < '1' || rhs[1] > '8') {
		setInvalid();
	}
	else {
		int c = rhs[0] - 'a';
		int r = rhs[1] - '1';
		set(c, r);
	}
	return *this;
}
const Position& Position::operator = (const string& rhs) {
	return (*this = rhs.c_str());
}

/*PIXELS*/
int Position::getX() const
{
	return isValid() ? (int)(squareWidth * (getCol() + 1)) : -1;
}
int Position::getY() const
{
	return isValid() ? (int)(squareHeight * (getRow() + 1)) : -1;
}
void Position::setXY(double x, double y)
{
	int c = (int)(x / squareWidth) - 1;
	int r = 8 - (int)(y / squareHeight);

	if (c < 0 || c > 7)
	{
		setInvalid();
		return;
	}

	if (r < 0 || r > 7)
	{
		colRow = (c << 4) | 0x0f;
		return;
	}

	set(c, r);
}
void Position::setBoardWidthHeight(int widthBoard, int heightBoard)
{
	if (widthBoard < 0 || heightBoard < 0)
		return;
	squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
	squareHeight = (double)heightBoard / 10.0;
}

double Position::getSquareWidth() const
{
	return squareWidth;
}

double Position::getSquareHeight() const
{
	return squareHeight;
}


/*DELTA MOVEMENT*/
Position::Position(const Position& rhs, const Delta& delta)
{
	colRow = rhs.colRow;
	adjustRow(delta.dRow);
	adjustCol(delta.dCol);
}

void Position::adjustRow(int dRow)
{
	if (!isValid())
		return;
	set(getCol(), getRow() + dRow);
}

void Position::adjustCol(int dCol)
{
	if (!isValid())
		return;
	set(getCol() + dCol, getRow());
}

const Position& Position::operator+=(const Delta& rhs)
{
	adjustRow(rhs.dRow);
	adjustCol(rhs.dCol);
	return *this;
}

Position Position::operator+(const Delta& rhs) const
{
	Position tmp(*this);
	tmp += rhs;
	return tmp;
}

/******************************************
 * PRIVATE SET
 ******************************************/
void Position::set(uint8_t colRowNew)
{
	colRow = colRowNew;
}