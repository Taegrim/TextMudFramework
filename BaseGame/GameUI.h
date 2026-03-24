#pragma once
#include "BaseUI.h"

class ScreenUI : public BaseUI
{
public:
	ScreenUI(int x, int y, unsigned int lines);

	void Render() override;
};


class MessageUI : public BaseUI
{
public:
	MessageUI(int x, int y, unsigned int lines);

	void Render() override;
};


class LogUI : public BaseUI
{
public:
	LogUI(int x, int y, unsigned int lines);

	void Render() override;
};


class MinimapUI : public BaseUI
{
public:
	MinimapUI(int x, int y, unsigned int lines);

	void Render() override;
};


class CharacterUI : public BaseUI
{
public:
	CharacterUI(int x, int y, unsigned int lines);

	void Render() override;
};