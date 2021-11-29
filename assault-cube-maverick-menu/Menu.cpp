#include "pch.h"
#include "Menu.h"
#include "openglDraw.h"
#include "Console.h"
#include "glut.h"

void DrawMenu(Menu m)
{
	int i = 0;
	for (MenuTab tab : m.tabArray)
	{
		drawString(m.xPos + i * 60, m.yPos + 16, 255, 0, 0, GLUT_BITMAP_9_BY_15, "%s", tab.tabName.c_str());
		i++;
	}
	i = 0;

	for (MenuOption option : m.tabArray.at(m.selectedTab).optionArray)
	{
		if(m.selectedOption == i)
			if(option.hack->getToggled())
				drawString(m.xPos, m.yPos + 32 + i * 16, 0, 255, 0, GLUT_BITMAP_9_BY_15, "%s [ ON ]", option.hack->name.c_str());
			else
				drawString(m.xPos, m.yPos + 32 + i * 16, 0, 255, 0, GLUT_BITMAP_9_BY_15, "%s [ OFF ]", option.hack->name.c_str());
		else
			if(option.hack->getToggled())
			drawString(m.xPos, m.yPos + 32 + i * 16, 255, 255, 255, GLUT_BITMAP_9_BY_15, "%s [ ON ]", option.hack->name.c_str());
		else
			drawString(m.xPos, m.yPos + 32 + i * 16, 255, 255, 255, GLUT_BITMAP_9_BY_15, "%s [ OFF ]", option.hack->name.c_str());
		i++;
	}

	line(1.0f, (m.xPos + (m.selectedTab * 60)), m.yPos + 18, (m.xPos + m.selectedTab * 60) + 45, m.yPos + 18, 255, 255, 255);
	box(0, 0,60 + 60 * (m.tabArray.size()-1), 100, 0, 0, 0);

}