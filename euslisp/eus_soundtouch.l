(defvar *eus-soundtouch-plugin*
  (labels
      ((library_search
	(str &key
	     (depth 0)
	     colon-pos lib-path)
	(format t "  [~A] target=" depth)
	(cond
	 ((eq (length str) 0)
	  (format t "~% eus-soundtouch_plugin_not_found in eiquadprog.l~%")
	  (exit -1))
	 ((and (setq colon-pos (or (position #\: str) (length str)))
	       (setq lib-path (subseq str 0 colon-pos))
	       (setq lib-path
		     (if (eq (aref lib-path (- (length lib-path) 1)) #\/)
			 (subseq lib-path 0 (- (length lib-path) 1))
		       lib-path))
	       (probe-file (setq lib-path
				 (print (format nil "~A/libeus_soundtouch.so" lib-path)))))
	  (load-foreign lib-path))
	 (t
	  (library_search (subseq str (min (length str) (+ colon-pos 1)))
			  :depth (+ depth 1))))))
    (library_search (format nil "~A:~A/lib"
			    (unix:getenv "LD_LIBRARY_PATH")
			    (ros::rospack-find "eus_soundtouch")))))

(defforeign set-param-sound-touch
  *eus-soundtouch-plugin*
  "setParamSoundTouch"
  (:integer :integer :double :double :double);; samplerate, channels, tempo, pitch, rate
  :integer)

(defforeign put-sample-sound-touch
  *eus-soundtouch-plugin*
  "putSampleSoundTouch"
  (:string :integer :integer)
  :integer)

(defforeign receive-sample-sound-touch
  *eus-soundtouch-plugin*
  "receiveSampleSoundTouch"
  (:string :integer :integer)
  :integer)

(defforeign flush-sound-touch
  *eus-soundtouch-plugin*
  "flushSoundTouch"
  ()
  :integer)

(defforeign init-sound-touch
  *eus-soundtouch-plugin*
  "initSoundTouch"
  ()
  :integer)

(defforeign open-in-wav-file
  *eus-soundtouch-plugin*
  "openInWavFile"
  (:string :string)
  :integer)

(defforeign open-out-wav-file
  *eus-soundtouch-plugin*
  "openOutWavFile"
  (:string :integer :integer :integer);; samplerates, bits. channels
  :integer)

(defforeign close-out-wav-file
  *eus-soundtouch-plugin*
  "closeOutWavFile"
  ()
  :integer)

(defforeign close-in-wav-file
  *eus-soundtouch-plugin*
  "closeInWavFile"
  ()
  :integer)

(defforeign read-wav-file
  *eus-soundtouch-plugin*
  "readWavFile"
  (:string :integer)
  :integer)

(defforeign write-wav-file
  *eus-soundtouch-plugin*
  "writeWavFile"
  (:string :integer)
  :integer)

(defun test-copy-wav-file
  (&key
   (inpath "voice.wav")
   (outpath "out.wav")
   ;; buf
   (info-buf (float-vector 0 0 0))
   (data-buf (instantiate float-vector 1024))
   size
   )
  (open-in-wav-file inpath info-buf)
  (open-out-wav-file outpath
		     (round (aref info-buf 0))
		     (round (aref info-buf 1))
		     (round (aref info-buf 2)))
  (while
  ;; (dotimes (i 5)
      (plusp (print (setq size (read-wav-file data-buf (length data-buf)))))
    (write-wav-file data-buf (/ size (max 1 (round (aref info-buf 2))))))
  (close-out-wav-file)
  (close-in-wav-file)
  )

(defun test-pitch-shift
  (&key
   (inpath "voice.wav")
   (outpath "out.wav")
   (tempo 0.0) (pitch 0.0) (rate 0.0)
   channels samplerate
   ;; buf
   (info-buf (float-vector 0 0 0))
   (data-buf (instantiate float-vector 1024))
   size
   )
  (open-in-wav-file inpath info-buf)
  (setq channels (round (aref info-buf 2)))
  (setq samplerate (round (aref info-buf 0)))
  (open-out-wav-file outpath
		     samplerate
		     (round (aref info-buf 1))
		     channels)
  (set-param-sound-touch samplerate channels tempo pitch rate)
  (while
      (plusp (setq size (read-wav-file data-buf (length data-buf))))
    (put-sample-sound-touch data-buf size channels)
    (while (plusp (print (setq size (receive-sample-sound-touch data-buf size channels))))
      (write-wav-file data-buf (/ size (max 1 channels)))))
  (flush-sound-touch)
  (while (plusp (setq size (receive-sample-sound-touch data-buf size channels)))
    (write-wav-file data-buf (/ size (max 1 channels))))
  ;;
  (close-out-wav-file)
  (close-in-wav-file)
  )

#|

roseus eus_soundtouch.l
(test-pitch-shift :pitch 5.0)
(exit)

;;test-copy-wav-file

