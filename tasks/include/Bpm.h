#ifndef __BPM_H__
#define __BPM_H__

#include "SinkTask.h"

namespace Tasks
{
  class BpmResult;

  typedef SinkTaskMgr<BpmResult> BpmManager;
  
  class BpmResult
  {
  public:
    BpmResult():
      beam_intensity(0),
      beam_center_x(0.),
      beam_center_y(0.),
      beam_fwhm_x(0.),
      beam_fwhm_y(0.),
      max_pixel_value(0),
      max_pixel_x(0),
      max_pixel_y(0),
      frameNumber(-1),
      AOI_automatic(true),
      AOI_extension_factor(4),
      AOI_min_x(-1),
      AOI_max_x(-1),
      AOI_min_y(-1),
      AOI_max_y(-1),
      border_exclusion(10),
      mBackgroundLevelx(0.),
      mBackgroundLevely(0.),
      mBackgroundLevelTunex(0.),
      mBackgroundLevelTuney(0.),
      errorCode(BpmManager::OK)
	{}

    explicit BpmResult(BpmManager::ErrorCode code) : errorCode(code) {}
	  
    double		beam_intensity;
    double		beam_center_x;
    double		beam_center_y;
    double		beam_fwhm_x;
    int		beam_fwhm_min_x_index;
    int		beam_fwhm_max_x_index;
    double		beam_fwhm_y;
    int		beam_fwhm_min_y_index;
    int		beam_fwhm_max_y_index;
    unsigned int	max_pixel_value;
    unsigned int	max_pixel_x;
    unsigned int	max_pixel_y;

    int		frameNumber;
      
    bool		AOI_automatic;
    unsigned int	AOI_extension_factor;
    int		AOI_min_x;
    int		AOI_max_x;
    int		AOI_min_y;
    int		AOI_max_y;
    unsigned int	border_exclusion;

    double		mBackgroundLevelx;
    double		mBackgroundLevely;
    double		mBackgroundLevelTunex;
    double		mBackgroundLevelTuney;

    BpmManager::ErrorCode	errorCode;
  private:
      
    void _setAOI(const int aRoi[])
    {
      AOI_min_x = aRoi[0];
      AOI_max_x = aRoi[1];
      AOI_min_y = aRoi[2];
      AOI_max_y = aRoi[3];
      AOI_automatic = false;
    }
  };

  class BpmTask : public SinkTask<BpmResult>
  {
  public:
    BpmTask(BpmManager &);
    BpmTask(const BpmTask&);
    virtual void process(Data&); 
      
    bool		mFwhmTunning;
    double		mFwhmTunningExtension;
    double		mAoiExtension;
    int			mBorderExclusion;
    unsigned int	mThreshold;
    bool		mEnableX;
    bool		mEnableY;
    bool		mEnableBackgroundSubstration;
    bool		mRoiAutomatic;
      
  private:
    template<class IN>
      void _treat_image(const Data &aSrc,
	                Buffer &projection_x,
		        Buffer &projection_y,
		        BpmResult &aResult);
    template<class IN> void _tune_projection(const Data &aSrc,
					     Buffer&,Buffer&,
					     const BpmResult&);
    double _calculate_fwhm(const Buffer &projection,int size,
			   int max_index,double background_level,
			   int &min_index,int &max_index);
    void _calculate_background(const Buffer &projection,double &background_level,
			       int min_index,int max_index);
  };
}
#endif