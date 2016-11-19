##LevelDB Structure


###Users network
- key: 
	`user_id : string`
- value:
```javascript
	{
		“network”: [ 
			id1,
			id2,
			…,
			idn
		],
		“count”: n
	}
```

### Chats
- key: 
	`user_id : string`
- value:
```javascript
	{
		“chats”: [
			chat_id1,
			chat_id2,
			…
			chat_idn
		],
		“total”: n
	}
```


### Chat (single)
- key: 
	`chat_id : string`
- value:
```javascript
	{	
		“participants” : [
			"user_id1",
			"user_id2",
			…,
			"user_idn"
		],
		“messages”: [
			{
				"user_id" : string,
				“message” : string,
				“timestamp” : int,	
			},
			{
				"user_id" : string,
				“message” : string,
				“timestamp” : int,
			},
			{
				"user_id" : string,
				“message” : string,
				“timestamp” : int,	
			},
			...
			{
				"user_id" : string,
				“message” : string,
				“timestamp” : int,
			}
		],
		“total”: n
	}
```
Note: The "messages" array is sorted by message timestamp.



###User

- key:
	`user_id : string`
- value:
```javascript
	{	
		“first_name” : string,
		“last_name” : string,
		"description" : string,
		“password” : string | encrypt
		“register_timestamp” : integer,
		“last_edit_timestamp” : integer,
		“email” : string,
		“date_of_birth”: string,
		“skills_names” : [
			name of skill : string,
			name of other skill : string
		],
		“jobs” : [
			{
				“date_since” : string,
				“date_to” : string (not required),
				“company” : string,
				“name_position” : string,
			}
		],
		“education” : [
			{
				“start_date” : string,
				“end_date” : string (not required),
				“school_name” : string,
				“degree” : string,
			}
		],
		“recommendations_received” : [
			{
				“recommender” : string,
				“text” : string,
				“timestamp” : integer 
			}
		]
	}
```

### Recommendations

- key: 
	`user_id : string`
- value:
```javascript
	{	
		“recommendations” : [
			{ 
				“user_id” : string,
				“description” : string,
				“timestamp” : integer 
			},
			{ 
				“user_id” : string,
				“description” : string,
				“timestamp” : integer 
			}
		]
		“total” : n
	}
```




###Skills
- key:
	`user_id : string`
- value:
```javascript
	{	
		“skills” : [
			skill1,
			skill2,
			…
			skilln
	]
	“total” : n
}
```

### User_Geolocalization
- key:
	`user_id : string`
- value:
	`geo_index : string`

### Geolocalization
- key:
	`geo_index : string`
- value:
```javascript
{
	"users" : {
		"user_id" : {
			"time_stamp" : string
			"geolocalization" : {
				"latitude" : float
				"longitude" : float
			}
		},
		...
		"user_id" : {
			"time_stamp" : string
			"geolocalization" : {
				"latitude" : float
				"longitude" : float
			}
		},
	}
}
```

</b>Nota: **geo_index** es una key formada por la union de la latitud y la longitud con una precision definida desde el modelo. 
Esto permite que se comporten como buckets que se encuentran a una distancia (haversine) constante.

Por ejemplo:
*lat: -25.2967829, lon: -57.5946782 === precision : 3 ===> geo_index = "-25.298-57.595"*


###Activity
- key: 
	`user_id : string`
- value:
```javascript
	{	
		“last_accion_timestamp” : integer
		"other_util_value" : anything
	}
```




###Configuration
- key:
	`key_name : string`
- value: 	
	`value : string`


