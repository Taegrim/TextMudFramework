#pragma once
#include "BaseUI.h"
#include "UIManager.h"

class ScreenUI : public BaseUI
{
public:
	ScreenUI(int x, int y, int lines) : BaseUI(x, y, lines) {}

	void Render() override;
};


class MessageUI : public BaseUI
{
public:
	MessageUI(int x, int y, int lines) : BaseUI(x, y, lines) {}

	void Render() override;
};


class LogUI : public BaseUI
{
public:
	LogUI(int x, int y, int lines) : BaseUI(x, y, lines) {}

	void Render() override;
};


class MinimapUI : public BaseUI
{
public:
	MinimapUI(int x, int y, int lines) : BaseUI(x, y, lines) {}

	void Render() override;
};


class CharacterUI : public BaseUI
{
public:
	CharacterUI(int x, int y, int lines) : BaseUI(x, y, lines) {}

	void Render() override;
};