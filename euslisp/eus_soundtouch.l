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

(defun test-eus-soundtouch
  (&rest
   args
   &key
   (a (float-vector 1 2 3 4))
   (b (instantiate float-vector (* 2 (length a))))
   (n (length a))
   )
  (format t " -- input value~% ~A~%" a)
  (fft-forward a b n)
  (format t " -- output value~% ~A~%" b)
  (fft-backward b a n)
  (format t " -- retransform~% ~A~%" a)
  )
