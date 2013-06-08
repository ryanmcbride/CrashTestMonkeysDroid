/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.LudicrousGames.MonkeyDroid;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHandler;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;

public class MonkeyDroid extends Cocos2dxActivity
{
	private static MonkeyDroid me = null;
	protected void onCreate(Bundle savedInstanceState)
	{
		
		System.out.println("***"+getWindowManager().getDefaultDisplay().getRefreshRate()+"***");
		me = this;
		super.onCreate(savedInstanceState);
	}

    static {
         System.loadLibrary("game");
    }
    
    public static void openURL(String url)
    {
    	Uri uri = Uri.parse(url);
    	Intent intent = new Intent(Intent.ACTION_VIEW, uri);
    	me.startActivity(intent);
    }
    
    public static void playMovie(String movieName)
    {   	
    	Message msg = new Message();
    	msg.what = Cocos2dxHandler.HANDLER_SHOW_VIDEO;
    	msg.obj = movieName;
    	me.mHandler.sendMessage(msg);
    }
    public static void stopMovie()
    {
    	Message msg = new Message();
    	msg.what = Cocos2dxHandler.HANDLER_STOP_VIDEO;
    	me.mHandler.sendMessage(msg);
    }
}
