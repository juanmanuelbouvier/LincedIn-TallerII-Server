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
			user_id1,
			user_id2,
			…,
			user_idn
		],
		“messages”: {,
			"user_id1" : [
				{
					“message” : string,
					“timestamp” : int,	
				},
				{
					“message” : string,
					“timestamp” : int,
				},
			],
			"user_id2" : [
				{
					“message” : string,
					“timestamp” : int,	
				},
				{
					“message” : string,
					“timestamp” : int,
				},
			]
		},
		“total”: n
	}
```




###User

- key:
	`user_id : string`
- value:
```javascript
	{	
		“name” : string,
		“surname” : string,
		“password” : string | encrypt
		“register_timestamp” : integer,
		“last_edit_timestamp” : integer,
		“mail” : string,
		“date_of_birth”: string,
		“current_job” : {
			“from_year” : string,
			“company” : string,
			“position” : string,
		},
		“past_jobs” : [
			{
				“from_year” : string,
				“company” : string,
				“position” : string,
			}
		],
		“education” : [
			{
				“start_date” : string,
				“end_date” : string,
				“school_name” : string,
				“degree” : string,
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


