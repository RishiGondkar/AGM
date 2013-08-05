/*
 *    Copyright (C) 2006-2012 by RoboLab - University of Extremadura
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EXECUTIVEVISUALIZATIONTOPICI_H
#define EXECUTIVEVISUALIZATIONTOPICI_H

#include <Ice/Ice.h>
#include <AGMExecutive.h>

#include <config.h>
#include "worker.h"

using namespace RoboCompAGMExecutive;

class AGMExecutiveVisualizationTopicI :  public virtual RoboCompAGMExecutive::AGMExecutiveVisualizationTopic
{
public:
	AGMExecutiveVisualizationTopicI(Worker *_worker)
	{
		printf("ExecutiveVisualizationTopicI(Worker *_worker)\n");
		worker = _worker;
	}
	void update(const RoboCompAGMWorldModel::World &world, const RoboCompAGMWorldModel::World &target, const RoboCompPlanning::Plan &plan, const Ice::Current & = Ice::Current())
	{
		worker->update(world, target, plan);
	}

private:
	Worker *worker;
};

#endif