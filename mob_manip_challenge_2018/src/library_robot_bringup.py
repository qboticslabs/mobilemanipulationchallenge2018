#!/usr/bin/env python

#Steps 

#1: Keep on checking for pick_gui service
#2: If availble call it and wait for finish: NB: Assume that the book is picked
#3: One finish, send goal position to navigation stack to goto the destination table
#4: Keep on checking whether the pose was successful
#5: If successful, call place
#6: After place, return back to the first table


import rospy

from std_srvs.srv import Empty


#This class comprises of all the functions to do this demo
class Library_Robot:

	def __init__(self):

		rospy.init_node('lib_manager_robot')
		rospy.loginfo("Starting Library Manager Robot interface")

		self.check_pick_service()




		rospy.loginfo("Finished SphericalService constructor")
                self.place_gui = rospy.Service("/place_gui", Empty, self.start_aruco_place)
                self.pick_gui = rospy.Service("/pick_gui", Empty, self.start_aruco_pick)


		


	#Function to check pick gui is available, return true if available
	def check_pick_service(self):

		try:

			rospy.loginfo("Waiting for PICK and Place Services")

			rospy.wait_for_service('pick_gui')
		
			rospy.loginfo("Pick Gui service is available")

			rospy.wait_for_service('place_gui')

			rospy.loginfo("Place Gui service is available")

			rospy.loginfo("Creating service call for pick and place")

		
			self.pick_service = rospy.ServiceProxy('pick_gui', Empty)

			self.pick_service = rospy.ServiceProxy('place_gui', Empty)

			return 1

		except:
			rospy.logwarn("Exception in Checking PICK and place service")
			return -1

		

	#Call Pick service one it available, and return if it is successfull
	def call_pick_service(self):
		pass
	
	#Send goal position to navigation stack once it receive output from pick service, and check it finish or not
	def send_goal_pose(self):
		pass

	#Once it successfull, call place, return if it is successfull
	def call_place_service(self):
		pass

	#Return back to old place once place is successfull
	def go_home(self):
		pass


if __name__ == "__main__":
	robot_obj = Library_Robot()

	



	

	
