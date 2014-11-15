(defvar *eus-fftw-plugin*
  (labels
      ((library_search
	(str &key
	     (depth 0)
	     colon-pos lib-path)
	(format t "  [~A] target=" depth)
	(cond
	 ((eq (length str) 0)
	  (format t "~% eus-fftw_plugin_not_found in eiquadprog.l~%")
	  (exit -1))
	 ((and (setq colon-pos (or (position #\: str) (length str)))
	       (setq lib-path (subseq str 0 colon-pos))
	       (setq lib-path
		     (if (eq (aref lib-path (- (length lib-path) 1)) #\/)
			 (subseq lib-path 0 (- (length lib-path) 1))
		       lib-path))
	       (probe-file (setq lib-path
				 (print (format nil "~A/libeus_fftw.so" lib-path)))))
	  (load-foreign lib-path))
	 (t
	  (library_search (subseq str (min (length str) (+ colon-pos 1)))
			  :depth (+ depth 1))))))
    (library_search (format nil "~A:~A/lib"
			    (unix:getenv "LD_LIBRARY_PATH")
			    (ros::rospack-find "eus_fftw")))))

(defforeign fft-forward
  *eus-fftw-plugin*
  "fft_forward"
  (:string :string :integer) ;; in out N
  :integer)

(defforeign fft-backward
  *eus-fftw-plugin*
  "fft_backward"
  (:string :string :integer) ;; in out N
  :integer)

(defun test-eus-fftw
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
