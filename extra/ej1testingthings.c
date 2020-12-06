    for(i=0; i<m; i++){
		if( pthread_create(&prov[i],NULL, (void*)suplies, (void*) NULL) ){
			printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
		}
    }
    for(i=0; i<n; i++){
		if( pthread_create(&clients[i],NULL, (void*)purcharse, (void*) NULL) ){
			printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			exit(EXIT_FAILURE);
		}
    }

    for(i=0; i<m; i++){
        if( pthread_join(prov[i],NULL) ){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE); 
        }
    }
    for(i=0; i<n; i++){
        if( pthread_join(clients[i],NULL) ){
		  	printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	exit(EXIT_FAILURE);
        }
    }

    //Good way

    if(m>n){
        for(i=0; i<m; i++){
            if( pthread_create(&prov[i],NULL, (void*)suplies, (void*) NULL) ){
			    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			    exit(EXIT_FAILURE);
		    }
            if(i<n){
                if( pthread_create(&clients[i],NULL, (void*)purcharse, (void*) NULL) ){
                    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
                    exit(EXIT_FAILURE);
                }
            }
        }
        for(i=0; i<m; i++){
            if( pthread_join(prov[i],NULL) ){
                printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
                exit(EXIT_FAILURE); 
            }
            if(i<n){
                if( pthread_join(clients[i],NULL) ){
		  	        printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	        exit(EXIT_FAILURE);
                }
            }
        }
    }
        

    }
    else{
        for(i=0; i<n; i++){
            if( pthread_create(&clients[i],NULL, (void*)purcharse, (void*) NULL) ){
                    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
                    exit(EXIT_FAILURE);
		    }
            if(i<m){
                if( pthread_create(&prov[i],NULL, (void*)suplies, (void*) NULL) ){
			    printf("[Error] failed to create a thread. Errno value: %d\n",errno);
			    exit(EXIT_FAILURE);
                }
            }
        }
        for(i=0; i<n; i++){
            if( pthread_join(clients[i],NULL) ){
		  	    printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
		  	    exit(EXIT_FAILURE);
            }
            if(i<m){
                if( pthread_join(prov[i],NULL) ){
                    printf("[Error] failed to wait a thread. Errno value: %d\n", errno);
                    exit(EXIT_FAILURE); 
                }
            }
        }
    }