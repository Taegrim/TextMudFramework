#pragma once
#include "BaseUI.h"

class ScreenUI : public BaseUI
{
public:
	ScreenUI(int x, int y, int lines) : BaseUI(x, y, lines) { max_messages = lines - 3; }

	void Render() override;
};


class MessageUI : public BaseUI
{
public:
	MessageUI(int x, int y, int lines) : BaseUI(x, y, lines) { max_messages = lines - 1; }

	void Render() override;
};


class LogUI : public BaseUI
{
public:
	LogUI(int x, int y, int lines) : BaseUI(x, y, lines) { max_messages = lines - 1; }

	void Render() override;
};


class MinimapUI : public BaseUI
{
public:
	MinimapUI(int x, int y, int lines) : BaseUI(x, y, lines) { max_messages = lines - 3; }

	void Render() override;
};


class CharacterUI : public BaseUI
{
public:
	CharacterUI(int x, int y, int lines) : BaseUI(x, y, lines) { max_messages = lines - 2; }

	void Render() override;
};