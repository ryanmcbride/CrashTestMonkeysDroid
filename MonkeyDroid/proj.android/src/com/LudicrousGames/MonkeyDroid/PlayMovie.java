package com.LudicrousGames.MonkeyDroid;

import android.app.Activity;
import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.VideoView;

public class PlayMovie extends Activity 
{
	private MediaPlayer.OnCompletionListener mOnCompletionListener;
	private static Context sContext = null;
	private VideoView videoView = null;
	
	public static Context getContext() 
	{
		return sContext;
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		overridePendingTransition(R.anim.fadein, R.anim.fadeout);
		setContentView(R.layout.playmovie);
		sContext = this;
		mOnCompletionListener = new MediaPlayer.OnCompletionListener() {
	        @Override
	        public void onCompletion (MediaPlayer mp) {
	        	stopVideo();
	        }
	    };
	    
	    startVideo();
	}
	@Override
    public boolean onTouchEvent(MotionEvent event) 
	{
		stopVideo();
		return super.onTouchEvent(event);
    }
	public void startVideo()
	{
		String fullFileName = "android.resource://"+getContext().getPackageName()+"/";
		Bundle extras = getIntent().getExtras();
		if (extras != null) {
		    String value = extras.getString("MovieName");
		    if(value.contentEquals("chimpodd"))
		    {
		    	fullFileName+=R.drawable.chimpodd;
		    }
		    else
				fullFileName+=R.drawable.onebanana;
		    	
		}
		else
			fullFileName+=R.drawable.onebanana;
		
		DisplayMetrics metrics = new DisplayMetrics(); 
		getWindowManager().getDefaultDisplay().getMetrics(metrics);
		ViewGroup.LayoutParams videoViewLayout_params =
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                           ViewGroup.LayoutParams.MATCH_PARENT);
        videoViewLayout_params.width = metrics.widthPixels;
        videoViewLayout_params.height = metrics.heightPixels;
		
        videoView = (VideoView)findViewById(R.id.myvideoview);
		
		videoView.setVideoURI(Uri.parse(fullFileName));
	    videoView.setVisibility(View.VISIBLE);
	    videoView.setOnCompletionListener(mOnCompletionListener);
	    //get focus, before playing the video.
	    videoView.requestFocus();
	    videoView.start();

	    
	}
	public void stopVideo()
	{
		videoView = (VideoView)findViewById(R.id.myvideoview);
		videoView.setVisibility(View.INVISIBLE);
		finish();
		overridePendingTransition(R.anim.fadein, R.anim.fadeout);
	}
}
