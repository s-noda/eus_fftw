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
  (:integer :integer :float :float :float)
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
  (:string :integer :integer :integer)
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

(defun test-eus-soundtouch
  (&key
   (inpath "voice.wav")
   (info-buf (integer-vector 0 0 0))
   (data-buf (instantiate integer-vector 1024))
   (outpath "out.wav")
   )
  (open-in-wav-file inpath info-buf)
  (open-out-wav-file outpath (aref info-buf 1) (aref info-buf 2))
  (read-wav-file data-buf (length data-buf))
  (write-wav-file data-buf (length data-buf))
  (close-out-wav-file)
  (close-in-wav-file)
  )
