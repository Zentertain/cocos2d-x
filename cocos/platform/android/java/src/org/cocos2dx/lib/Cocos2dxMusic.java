/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

package org.cocos2dx.lib;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.util.Log;

import java.io.FileInputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashMap;
import java.util.Map;

public class Cocos2dxMusic {

    private enum MediaStatus {
        MEDIA_STATUS_READY,
        MEDIA_STATUS_PLAYING,
        MEDIA_STATUS_STOP,
        MEDIA_STATUS_PAUSE
    }
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = Cocos2dxMusic.class.getSimpleName();
    private static final int MAX_MEDIA_CACHE_COUNT = 3;

    // ===========================================================
    // Fields
    // ===========================================================

    private final Context mContext;
    private MediaMusic mBackgroundMediaPlayer;
    private float mLeftVolume;
    private float mRightVolume;

    private boolean mManualPaused = false; // whether music is paused manually before the program is switched to the background.
    private String mCurrentPath;

    public class LRUCache<K, V> extends LinkedHashMap<K, V> {
        private int cacheSize;

        public LRUCache(int cacheSize) {
            super(16, 0.75f, true);
            this.cacheSize = cacheSize;
        }

        protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
            return size() > cacheSize;
        }
    }

    private class MediaMusic {
        private MediaPlayer mediaPlayer;
        private boolean isLoop;
        private MediaStatus status;

        public MediaPlayer getMediaPlayer() {
            return mediaPlayer;
        }

        public void setMediaPlayer(MediaPlayer mediaPlayer) {
            this.mediaPlayer = mediaPlayer;
        }

        public boolean isLoop() {
            return isLoop;
        }

        public void setLoop(boolean loop) {
            isLoop = loop;
        }

        public MediaStatus getStatus() {
            return status;
        }

        public void setStatus(MediaStatus status) {
            this.status = status;
        }

        public boolean isPaused() {
            return this.status == MediaStatus.MEDIA_STATUS_PAUSE;
        }
    }


    private LRUCache<String, MediaMusic> mBackgroundMediaPlayerMap = new LRUCache<>(MAX_MEDIA_CACHE_COUNT);

    // ===========================================================
    // Constructors
    // ===========================================================

    public Cocos2dxMusic(final Context context) {
        this.mContext = context;

        this.initData();
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    public void preloadBackgroundMusic(final String path) {
        Log.i(TAG, "preloadBackgroundMusic:" + path);
        if ((this.mCurrentPath == null) || (!this.mCurrentPath.equals(path)) || !this.mBackgroundMediaPlayerMap.containsKey(path)) {
            // preload new background music
            this.mBackgroundMediaPlayer = this.createMediaPlayer(path);

            this.addToMediaPlayerMap(path, this.mBackgroundMediaPlayer);

            // record the path
            this.mCurrentPath = path;
        }
    }

    public void playBackgroundMusic(final String path, final boolean isLoop) {
        if (mCurrentPath == null && !this.mBackgroundMediaPlayerMap.containsKey(path)) {
            // it is the first time to play background music or end() was called
            mBackgroundMediaPlayer = createMediaPlayer(path);
            mBackgroundMediaPlayer.setLoop(isLoop);
            this.addToMediaPlayerMap(path, this.mBackgroundMediaPlayer);
            mCurrentPath = path;
        } else {
            if (this.mBackgroundMediaPlayerMap.containsKey(path)) {
                mBackgroundMediaPlayer = this.mBackgroundMediaPlayerMap.get(path);
                mCurrentPath = path;
            } else if (!mCurrentPath.equals(path)) {
                // play new background music
                mBackgroundMediaPlayer = createMediaPlayer(path);
                this.addToMediaPlayerMap(path, this.mBackgroundMediaPlayer);
                mBackgroundMediaPlayer.setLoop(isLoop);
                // record the path
                mCurrentPath = path;
            }
        }

        if (mBackgroundMediaPlayer == null) {
            Log.e(Cocos2dxMusic.TAG, "playBackgroundMusic: background media player is null");
        } else {
            try {
                // if the music is playing or paused, stop it
                mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PLAYING);
                if (mBackgroundMediaPlayer.isPaused()) {
                    mBackgroundMediaPlayer.getMediaPlayer().seekTo(0);
                    mBackgroundMediaPlayer.getMediaPlayer().start();
                } else if (mBackgroundMediaPlayer.getMediaPlayer().isPlaying()) {
                    mBackgroundMediaPlayer.getMediaPlayer().seekTo(0);
                } else {
                    mBackgroundMediaPlayer.getMediaPlayer().start();
                }
                mBackgroundMediaPlayer.getMediaPlayer().setLooping(isLoop);
                mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PLAYING);
            } catch (final Exception e) {
                Log.e(Cocos2dxMusic.TAG, "playBackgroundMusic: error state");
            }
        }
    }

    public void stopBackgroundMusic() {
        if (this.mBackgroundMediaPlayer != null) {
            mBackgroundMediaPlayer.getMediaPlayer().pause();
            mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_STOP);
            /**
             * should set the state, if not, the following sequence will be error
             * play -> pause -> stop -> resume
             */
        }
    }

    public void pauseBackgroundMusic() {
        try {
            if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.getMediaPlayer().isPlaying()) {
                this.mBackgroundMediaPlayer.getMediaPlayer().pause();
                this.mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PAUSE);
                this.mManualPaused = true;
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "pauseBackgroundMusic, IllegalStateException was triggered!");
        }
    }

    public void resumeBackgroundMusic() {
        try {
            if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPaused()) {
                this.mBackgroundMediaPlayer.getMediaPlayer().start();
                this.mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PLAYING);
                this.mManualPaused = false;
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "resumeBackgroundMusic, IllegalStateException was triggered!");
        }
    }

    public void rewindBackgroundMusic() {
        if (this.mBackgroundMediaPlayer != null) {
            playBackgroundMusic(mCurrentPath, this.mBackgroundMediaPlayer.isLoop());
        }
    }

    public boolean isBackgroundMusicPlaying() {
        boolean ret = false;
        try {
            if (this.mBackgroundMediaPlayer == null) {
                ret = false;
            } else {
                ret = this.mBackgroundMediaPlayer.getMediaPlayer().isPlaying();
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "isBackgroundMusicPlaying, IllegalStateException was triggered!");
        }

        return ret;
    }

    public void end() {
        if (this.mBackgroundMediaPlayer != null) {
            this.mBackgroundMediaPlayer.getMediaPlayer().release();
        }

        for(String key : this.mBackgroundMediaPlayerMap.keySet()){
            MediaMusic mediaMusic = this.mBackgroundMediaPlayerMap.get(key);
            if (mediaMusic != null) {
                mediaMusic.getMediaPlayer().release();
            }
        }
        this.mBackgroundMediaPlayerMap.clear();

        this.initData();
    }

    public float getBackgroundVolume() {
        if (this.mBackgroundMediaPlayer != null) {
            return (this.mLeftVolume + this.mRightVolume) / 2;
        } else {
            return 0.0f;
        }
    }

    public void setBackgroundVolume(float volume) {
        if (volume < 0.0f) {
            volume = 0.0f;
        }

        if (volume > 1.0f) {
            volume = 1.0f;
        }

        this.mLeftVolume = this.mRightVolume = volume;
        if (this.mBackgroundMediaPlayer != null) {
            this.mBackgroundMediaPlayer.getMediaPlayer().setVolume(this.mLeftVolume, this.mRightVolume);
        }
    }

    public void onEnterBackground(){
        try {
            if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.getMediaPlayer().isPlaying()) {
                this.mBackgroundMediaPlayer.getMediaPlayer().pause();
                mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PAUSE);
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "onEnterBackground, IllegalStateException was triggered!");
        }
    }
    
    public void onEnterForeground() {
        try {
            if (!this.mManualPaused) {
                if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPaused()) {
                    this.mBackgroundMediaPlayer.getMediaPlayer().start();
                    mBackgroundMediaPlayer.setStatus(MediaStatus.MEDIA_STATUS_PLAYING);
                }
            }
        } catch (IllegalStateException e) {
            Log.e(TAG, "onEnterForeground, IllegalStateException was triggered!");
        }
    }
    
    private void initData() {
        this.mLeftVolume = 0.5f;
        this.mRightVolume = 0.5f;
        this.mBackgroundMediaPlayer = null;
        this.mCurrentPath = null;
    }

    /**
     * create MediaPlayer for music
     * 
     * @param path The path relative to assets
     * @return
     */
    private MediaMusic createMediaPlayer(final String path) {
        MediaPlayer mediaPlayer = new MediaPlayer();

        try {
            if (path.startsWith("/")) {
                final FileInputStream fis = new FileInputStream(path);
                mediaPlayer.setDataSource(fis.getFD());
                fis.close();
            } else {
                if (Cocos2dxHelper.getObbFile() != null) {
                    final AssetFileDescriptor assetFileDescriptor = Cocos2dxHelper.getObbFile().getAssetFileDescriptor(path);
                    mediaPlayer.setDataSource(assetFileDescriptor.getFileDescriptor(), assetFileDescriptor.getStartOffset(), assetFileDescriptor.getLength());
                } else {
                    final AssetFileDescriptor assetFileDescriptor = this.mContext.getAssets().openFd(path);
                    mediaPlayer.setDataSource(assetFileDescriptor.getFileDescriptor(), assetFileDescriptor.getStartOffset(), assetFileDescriptor.getLength());
                }
            }

            mediaPlayer.prepare();

            mediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
        } catch (final Exception e) {
            mediaPlayer = null;
            Log.e(Cocos2dxMusic.TAG, "error: " + e.getMessage(), e);
        }

        MediaMusic mediaMusic = new MediaMusic();
        mediaMusic.setMediaPlayer(mediaPlayer);
        mediaMusic.setStatus(MediaStatus.MEDIA_STATUS_READY);
        return mediaMusic;
    }

    private void addToMediaPlayerMap(String path, MediaMusic mediaMusic) {
        if (!this.mBackgroundMediaPlayerMap.containsKey(path)) {
            this.mBackgroundMediaPlayerMap.put(path, mediaMusic);
        }
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
