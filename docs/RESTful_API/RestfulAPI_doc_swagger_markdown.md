LincedIn - Server API
=====================
API para el server de LincedIn

**Version** 1.0
### /search
---
##### ***GET***
**Summary:** Busqueda de personas

**Description:** Se podrá realizar una búsqueda sobre los profesionales que posee el sistema y ver la información asociada. Esta búsqueda puede ser parametrizable, se puede realizar una búsqueda por palabras claves, skills y un cierto rango de distancia a partir de la geolocalización actual del usuario. Además se podrá ordenar, por fecha, alfabéticamente y por popularidad.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| text | query | Texto a buscar | No | string |
| skill | query | Skills | No | array.string |
| geo | query | Latitud, Longitud para buscar cercanos | No | string |


**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Resultados de la búsqueda |
| 500 | Unexpected error |

**Body (resultado de la búsqueda)**
Retorna un json con usuarios que machean en la búsqueda.

```javascript
 {
    "users_found" : [
          "UserID1",
          "UserID2",
          "UserID3",
          ...
    ]
 }
```

### /friends/{destination_user_id}
---
##### ***POST***
**Summary:** Enviar y, en caso de ya existir, solicitud para formar parte de la red.

**Description:** El servidor proveerá un servicio en donde el usuario podrá mandar una solicitud al contacto para que pueda ser parte de su red profesional. El usuario destinatario puede aceptar dicha solicitud.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |
| destination_user_id | path | Usuario Destino | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Solicitud para agregar a la red enviada |
| 202 | Solicitud para agregar a la red aceptada |
| 401 | Token de acceso invalido |
| 404 | Usuario destino inexistente |
| 408 | Usuario ya es parte de la red |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Rechazar solicitud para formar parte o eliminar contacto de la red

**Description:** El usuario puede rechazar un solicitud que le ha sido enviada. Tambien, elimina


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |
| destination_user_id | path | Usuario Destino | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 204 | Usuario eliminado de la red |
| 401 | Token de acceso invalido |
| 404 | Usuario destino inexistente |
| 408 | Usuario no es parte de la red |
| 412 | Solicitud no puede ser rechazada debido a su inexistencia. |

### /friends
---
##### ***GET***
**Summary:** Solicitar todos los usuarios que forman parte de la red (amigos).

**Description:** El servidor proveerá un listado de usuarios los cuales formen parte de la red de amigos del usuario correspondiente al token de acceso (solo usuarios que aceptaron la solicitud).

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Listado de usuarios que forman parte de la red |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "friends" : [
          "UserID1",
          "UserID2",
          "UserID3",
          ...
    ],
    "online" : [
          "UserID1",
          "UserID2",
          "UserID3",
          ...
    ],
    "metadata" : {
          "total": int, //cantidad de usuarios amigos
          "version": string // versión de la api
    }
 }
```

### /friends/pending
---
##### ***GET***
**Summary:** Solicitar todos los usuarios pendientes para formar parte de la red (amigos).

**Description:** El servidor proveerá un listado de usuarios que estén pendientes para formar parte de la red, ya sea por que no aceptaron la solicitud o por que el usuario que solicita el recurso no acepto la solicitud.

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Listado de usuarios pendientes |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "friends" : [
          "UserID1",
          "UserID2",
          "UserID3",
          ...
    ],
    "metadata" : {
          "total": int, //cantidad de usuarios amigos
          "version": string // versión de la api
    }
 }
```

### /chat
---
##### ***GET***
**Summary:** Listado de conversaciones

**Description:** Posibilidad de acceder a todas las conversaciones realizadas.

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Todas los chats existentes |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "chats" : [
          {
            "chat_id" : string,
            "participants" : [UserID1, UserID2, ....],
            "last_message" : {
                                "message": string,
                                "user_id": string,
                                "timestamp": int
                             } 
          },
          ...
    ],
    "metadata" : {
          "total": int, //cantidad de usuarios amigos
          "version": string // versión de la api
    }
 }
```

### /chat/online
---
##### ***GET***
**Summary:** Listado de usuarios que están online.

**Description:** Posibilidad de ver los usuarios activos que forman parte de la red.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Todas los usuarios online pertenecientes a la red. |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "friends_online" : [
          UserId1,
          UserId2,
          ...
    ],
    "metadata" : {
          "total": int, //cantidad de usuarios amigos
          "version": string // versión de la api
    }
 }
```

### /chat/{chat_id}
---
##### ***GET***
**Summary:** Obtener conversación

**Description:** Obtener el listado de mensajes correspondientes al chat, el orden es cronológico desde desde el mas nuevo al mas antiguo.

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |
| chat_id | path | Identificador del chat. | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Conversación |
| 404 | Conversación no existente |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "participants" : [ UserID1,UserID2, ...],
    "messages" : [
                     {
                       "message": string,
                       "user_id": string
                       "timestamp": int
                     },
                     ...
                 ]
 }
```

##### ***POST***
**Summary:** Enviar mensaje

**Description:** Enviar un mensaje en una conversación.

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |
| destination_user_id | path | Usuario destino en la conversación. | Yes | string |
| body | body | mensaje a enviar | No | undefined |

*Body*
```javascript
 {
    "message" : string 
 }
```

**Responses**

| Code | Description |
| ---- | ----------- |
| 201 | Mensaje enviado |
| 401 | Token de acceso invalido |
| 400 | Incumplimiento de las condiciones |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Eliminar conversación

**Description:** Se permite eliminar conversación con usuario/s.

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |
| chat_id | path | Id de la conversación. | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 204 | Conversación eliminada |
| 404 | No existe conversación |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

### /user
---
##### ***POST***
**Summary:** crear usuario

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| body | body | Información del usuario | Yes | undefined |

**Body**
```javascript
 {
    "id" : string, // opcional: Id que uno pretende, si no es valido se asigna otro determinado por el sistema.
    "first_name" : string,
    "last_name" : string,
    "description" : string,
    "email" : string,
    "date_of_birth" : string datetime,
    "profile_picture" : string, //imagen en base 64.
    "password" : string, //opcional: si no es creada por el sistema.
    
    //campos opcionales al momento de la creación
    "skills" : [ 
        {
         "name" : string,
         "description" : string,
         "category" : string
        },
        ...
    ],
    "jobs" : [
        {
        "date_since" : string,
        "date_to" : string,
        "company" : string,
        "position" : {
                      "name" : string,
                      "description" : string,
                      "category" : string
                     }
        },
        ...
    ],
    "educations" : [
        {
         "date_since" : string,
         "date_to" : string,
         "school_name" : string,
         "degree" : string
        },
        ...
    ]
 }
```

**Responses**

| Code | Description |
| ---- | ----------- |
| 201 | Usuario dado de alta |
| 400 | Parametros invalidos |
| 500 | Unexpected error |

### /user/{user_id}
---
##### ***GET***
**Summary:** Perfil del usuario indicado

**Description:** ** Descripcion **

** **

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Perfil de usuario en cuestion |
| 404 | Usuario inexistente |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

**Body**
```javascript
 {
    "id" : string,
    "first_name" : string,
    "last_name" : string,
    "description" : string,
    "email" : string,
    "date_of_birth" : string datetime,
    "profile_picture" : string, //url to load image in base64
    "skills" : [ 
        {
         "name" : string,
         "description" : string,
         "category" : string
        },
        ...
    ],
    "jobs" : [
        {
        "date_since" : string,
        "date_to" : string,
        "company" : string,
        "position" : {
                            "name" : string,
                            "description" : string,
                            "category" : string
                          }
        },
        ...
    ],
    "educations" : [
        {
         "date_since" : string,
         "date_to" : string,
         "school_name" : string,
         "degree" : string
        },
        ...
    ]
 }
```
##### ***PUT***
**Summary:** Modificar perfil

**Description:** ** Descripcion **


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso referido al user id | Yes | string |
| body | body | Informacion a modificar | Yes | undefined |

**Body**
```javascript
 {
    "id" : string,
    "first_name" : string,
    "last_name" : string,
    "description" : string,
    "email" : string,
    "date_of_birth" : string datetime,
    "profile_picture" : string, //image en base64, si no está definido no se cambia.
    "skills" : [
        {
         "name" : string,
         "description" : string,
         "category" : string
        },
        ...
    ],
    "jobs" : [
        {
        "date_since" : string,
        "date_to" : string,
        "company" : string,
        "position" : {
                            "name" : string,
                            "description" : string,
                            "category" : string
                          }
        },
        ...
    ],
    "educations" : [
        {
         "date_since" : string,
         "date_to" : string,
         "school_name" : string,
         "degree" : string
        },
        ...
    ]
 }
```

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Perfil modificado. |
| 400 | Parametros invalidos |
| 404 | Usuario inexistente |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Eliminar perfil

**Description:** El usuario tiene el derecho de eliminarse de la plataforma

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 204 | Perfil eliminado |
| 404 | Usuario inexistente |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

### /user/me
---
##### ***GET***
**Summary:** Perfil del usuario correspondiente al token. Igual a /user/{user_id}.

### /img/{id}
---
##### ***GET***
**Summary:** Imagen correspondiente

**Description:** El usuario puede obtener la imagen si tiene el id

**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Imagen |
| 404 | imagen inexistente |
| 401 | Token de acceso invalido |
| 500 | Unexpected error |

**Body**
```javascript
 {
   "info" : string, //ej: "data:image/jpeg;base64"
   "name" : string, 
   "content" : string, //base64 de la imagen
 }
```

### /recommendation/{user_id}
---
##### ***GET***
**Summary:** Obtener recomendaciones de usuario

**Description:** Listar todas las recomendaciones de un usuario

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Recomendaciones |
| 404 | Usuario Inexistente |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "recommendations_sent" : [UserId1,UserId2,...],
    "recommendations_received" : [UserId1,UserId2,...],
 }
```

##### ***POST***
**Summary:** Recomendar a un usuario.

**Description:** Se genera una recomendación con una descripcion.

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | ---- |
| 401 | Token Invalido |
| 402 | Parametros invalidos |
| 404 | Usuario Inexistente |
| 408 | Recomendacion ya fue realizada |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Eliminar recomendacion.

**Description:** Eliminar recomendacion anteriormente realizada.

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | ---- |
| 401 | Token Invalido |
| 404 | Usuario Inexistente |
| 410 | Recomendacion no fue realizada |
| 500 | Unexpected error |


### /geolocalization/{user_id}
---
##### ***GET***
**Summary:** Obtener ubicacion de un usuario

**Description:** Listar todas las recomendaciones de un usuario

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Recomendaciones |
| 404 | Usuario Inexistente |
| 500 | Unexpected error |

*Body*
```javascript
 {
    "latitude" : string,
    "longitude" : string,
    "timestamp" : int 
 }

### /geolocalization*?range=..&latitude..&longitude*
---
##### ***GET***
**Summary:** Obtener ubicación de usuarios cercanos

**Description:** A partir de una ubicación y un rango se obtienen los usuarios dentro del mismo

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| range | query | Rango de busqueda | Yes | string |
| latitude | query | Latitud | Yes | string |
| longitude | query | Longitud | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Usuarios cercanos |
| 404 | Parametros invalidos |
| 500 | Unexpected error |

*Body*
```javascript
 {
   "UserID1" : {
                  "latitude" : string,
                  "longitude" : string,
                  "timestamp" : int,
                  "distance" : double
               }
  ...
 }
```

---
##### ***POST***
**Summary:** Subir ubicacion al sistema.

**Description:** Registrar ubicacion de un usuario

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| Authorization | header | Token de acceso | Yes | string |

*Body*
```javascript
 {
    "latitude" : string,
    "longitude" : string
 }
```

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Recomendacion |
| 401 | Token Invalido |
| 404 | Parametros invalidos |
| 500 | Unexpected error |
