import os
import rospkg
import rospy

from std_srvs.srv import Empty
from move_base_msgs.msg import *
import actionlib

from qt_gui.plugin import Plugin
from python_qt_binding import loadUi
from python_qt_binding.QtWidgets import QWidget

class MyPlugin(Plugin):

    def __init__(self, context):
        super(MyPlugin, self).__init__(context)
        # Give QObjects reasonable names
        self.setObjectName('MyPlugin')
        rp = rospkg.RosPack()

        # Process standalone plugin command-line arguments
        from argparse import ArgumentParser
        parser = ArgumentParser()
        # Add argument(s) to the parser.
        parser.add_argument("-q", "--quiet", action="store_true",
                      dest="quiet",
                      help="Put plugin in silent mode")
        args, unknowns = parser.parse_known_args(context.argv())
        if not args.quiet:
            print 'arguments: ', args
            print 'unknowns: ', unknowns

        # Create QWidget
        self._widget = QWidget()
        # Get path to UI file which is a sibling of this file
        # in this example the .ui and .py file are in the same folder
        ui_file = os.path.join(rp.get_path('mob_manip_gui'), 'resource', 'MyPlugin.ui')
        # Extend the widget with all attributes and children from UI file
        loadUi(ui_file, self._widget)
        # Give QObjects reasonable names
        self._widget.setObjectName('MyPluginUi')
        # Show _widget.windowTitle on left-top of each plugin (when 
        # it's set in _widget). This is useful when you open multiple 
        # plugins at once. Also if you open multiple instances of your 
        # plugin at once, these lines add number to make it easy to 
        # tell from pane to pane.
        if context.serial_number() > 1:
            self._widget.setWindowTitle(self._widget.windowTitle() + (' (%d)' % context.serial_number()))
        # Add widget to the user interface
        context.add_widget(self._widget)


	self.book_no = 0

	self.book_shelf_pose = [[1.01864218712,-7.92231225967,0,  0,0,0.0314119279953,0.99950652363],
			     [1.03648173809,-9.72018623352,0,  0,0,0.0445468954746,0.99900729432],
			     [1.01864218712,-7.92231225967,0,  0,0,0.0314119279953,0.99950652363],
			     [1.03648173809,-9.72018623352,0,  0,0,0.0445468954746,0.99900729432],
			    ]


        self._widget.pushButton.clicked[bool].connect(self.go_robot)

        self._widget.radioButton.clicked[bool].connect(self.book_one)
        self._widget.radioButton_2.clicked[bool].connect(self.book_two)
        self._widget.radioButton_3.clicked[bool].connect(self.book_three)
        self._widget.radioButton_4.clicked[bool].connect(self.book_four)



    def book_one(self):
	self.book_no = 0	


    def book_two(self):
	self.book_no = 1	


    def book_three(self):
	self.book_no = 2	

    def book_four(self):
	self.book_no = 3	





    def go_robot(self):
	rospy.loginfo("Assisting robot to the destination, to find book = %d", self.book_no)



	self.client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
	self.goal = MoveBaseGoal()

		
	rospy.loginfo("Waiting for Move base server")
	self.client.wait_for_server()

	
	self.goal.target_pose.pose.position.x=float(self.book_shelf_pose[self.book_no][0])
	self.goal.target_pose.pose.position.y=float(self.book_shelf_pose[self.book_no][1])
	self.goal.target_pose.pose.position.z=float(self.book_shelf_pose[self.book_no][2])

	self.goal.target_pose.pose.orientation.x = float(self.book_shelf_pose[self.book_no][3])
	self.goal.target_pose.pose.orientation.y= float(self.book_shelf_pose[self.book_no][4])
	self.goal.target_pose.pose.orientation.z= float(self.book_shelf_pose[self.book_no][5])
	self.goal.target_pose.pose.orientation.w= float(self.book_shelf_pose[self.book_no][6])

	self.goal.target_pose.header.frame_id= 'map'
	self.goal.target_pose.header.stamp = rospy.Time.now()

	rospy.loginfo("Sending Goal position to the robot")
	self.client.send_goal(self.goal)


	

    def shutdown_plugin(self):
        # TODO unregister all publishers here
        pass

    def save_settings(self, plugin_settings, instance_settings):
        # TODO save intrinsic configuration, usually using:
        # instance_settings.set_value(k, v)
        pass

    def restore_settings(self, plugin_settings, instance_settings):
        # TODO restore intrinsic configuration, usually using:
        # v = instance_settings.value(k)
        pass

    #def trigger_configuration(self):
        # Comment in to signal that the plugin has a way to configure
        # This will enable a setting button (gear icon) in each dock widget title bar
        # Usually used to open a modal configuration dialog
