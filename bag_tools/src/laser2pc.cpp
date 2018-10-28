#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>

class My_Filter {
     public:
        My_Filter();
        void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
     private:
        ros::NodeHandle node_;
		ros::NodeHandle node_p;
        laser_geometry::LaserProjection projector_;
        tf::TransformListener tfListener_;

        ros::Publisher point_cloud_publisher_;
        ros::Subscriber scan_sub_;
        
        //parameters
        std::string pc_frame_;
        std::string scan_topic_;
};

My_Filter::My_Filter(){
		node_p = ros::NodeHandle("~");
		node_p.param<std::string>("pc_frame", pc_frame_,"odom");
		node_p.param<std::string>("scan_topic", scan_topic_, "/scan");
        
        scan_sub_ = node_.subscribe<sensor_msgs::LaserScan> (scan_topic_, 2, &My_Filter::scanCallback, this);
        point_cloud_publisher_ = node_.advertise<sensor_msgs::PointCloud2> ("/pc2", 2, false);
        tfListener_.setExtrapolationLimit(ros::Duration(0.1));
}

void My_Filter::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
    sensor_msgs::PointCloud2 cloud;
    try
    {
		projector_.transformLaserScanToPointCloud(pc_frame_, *scan, cloud, tfListener_);
		point_cloud_publisher_.publish(cloud);
    }
    catch(tf2::LookupException& ex)
	{
    	ROS_ERROR("scan to pc Lookup Exception");
	}
    catch(tf2::ExtrapolationException& ex)
    {
    	unsigned nt = 0;
    	bool valid_tf = false;
    	while(!valid_tf)
    	{
			try
			{
				projector_.transformLaserScanToPointCloud(pc_frame_, *scan, cloud, tfListener_);
				valid_tf = true;
				point_cloud_publisher_.publish(cloud);
			}
			catch(tf2::ExtrapolationException& ex)
			{
				++nt;
			}
    	}
    	//ROS_INFO("pc nt: %d",nt);
    	//if(!valid_tf)
    	//	ROS_ERROR("scan to pc Extrapolation Exception");
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_filter");
    ROS_INFO("laser2pc started");

    My_Filter filter;

    ros::spin();

    return 0;
}
