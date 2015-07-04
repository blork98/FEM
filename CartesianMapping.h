#ifndef CARTESIAN_MAPPING_H_
#define CARTESIAN_MAPPING_H_

#include <Mapping.h>

class BilinearQuadMapping2D : public Mapping 
{
public:
	BilinearQuadMapping2D( 
        const std::vector<std::pair<double,double>>& nodeLocationsMaster);

    void transform_real_to_master( 
		const std::vector<double>& rPoint, std::vector<double>& mPoint) const;
    void transform_master_to_real( 
		const std::vector<double>& mPoint, std::vector<double>& rPoint) const;
    void get_jacobian_matrix( std::vector<double>& jMat, double& jacobian) const;
    
    void set_point(const std::vector<double>& evalPoint);
    void set_node_locations( const std::vector<std::pair<double,double> >& nodeLocations);
    void set_node_locations_master( const std::vector<std::pair<double,double> >& nodeLocations);

private:
    double jacobian(const std::pair<double,double>& point) const;
    double shape_value(const unsigned int& node, const std::pair<double,double>& point) const;
    std::pair<double,double> shape_grad_value( const unsigned int& node, 
                                        const std::pair<double,double>& point) const;

    std::vector<std::pair<double,double>> nodeLocations_, nodeLocationsMaster_;
    std::pair<double,double> evalLocation_;
    unsigned int numNodes_;   
    //cached values
    void reset_vals();
    void calculate_cached_values( const std::pair<double,double>& point );
    std::vector<double> cachedVals_;
};

#endif