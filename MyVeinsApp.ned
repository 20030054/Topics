//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

//
// network description file for your Veins Application. Add parameters here
//
simple MyVeinsApp extends DemoBaseApplLayer
{
    @class(veins::MyVeinsApp);
    string appName = default("My first Veins App!");
    double CH_HB_Interval=default(2);
    double CM_HB_Interval=default(2);
    double CM_Task_Interval =default(5);
    
    @signal[numSent](type="float");
	@statistic[numSent](title="numSent"; source="numSent"; record=stats, vector; interpolationmode=none); 
	
	@signal[systemDelay](type="float");
	@statistic[systemDelay](title="systemDelay"; source="systemDelay"; record=stats, vector; interpolationmode=none); 
	
	@signal[queueDelay](type="float");
	@statistic[queueDelay](title="queueDelay"; source="queueDelay"; record=stats, vector; interpolationmode=none); 
	
	@signal[serverDelay](type="float");
	@statistic[serverDelay](title="serverDelay"; source="serverDelay"; record=stats,vector; interpolationmode=none); 
	
	@signal[queueSize](type="float");
	@statistic[queueSize](title="queueSize"; source="queueSize"; record=stats,vector; interpolationmode=none); 

    
}
