LincedIn - Server API
=====================
API para el server de LincedIn

**Version** Alpha 0.1
### /search
---
##### ***GET***
**Summary:** Busqueda de personas

**Description:** Se podrá realizar una búsqueda sobre los profesionales que posee el sistema y ver la información asociada. Esta búsqueda puede ser parametrizable, se puede realizar una búsqueda por palabras claves, skills, un cierto rango de distancia a partir de la geolocalización actual del usuario. Además se podrá ordenar, por fecha, alfabeticamente y por popularidad.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| search_query | query | Texto a buscar | No | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Resultados de la búsqueda |
| 500 | Unexpected error |

### /friends/{destination_user_id}
---
##### ***POST***
**Summary:** Enviar y, en caso de ya existir, solicitud para formar parte de la red.

**Description:** El servidor proveerá un servicio en donde el usuario podrá mandar una solicitud al contacto para que pueda ser parte de su red profesional. El usuario destinatario puede aceptar dicha solicitud.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso | Yes | string |
| destination_user_id | path | Usuario Destino | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 202 | Solicitud para agregar a la red enviada |
| 204 | Solicitud para agregar a la red aceptada |
| 400 | Token de acceso invalido |
| 404 | Usuario destino inexistente |
| 408 | Usuario ya es parte de la red |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Rechazar solicitud para formar parte o eliminar contacto de la red

**Description:** El usuario puede rechazar un solicitud que le ha sido enviada. Tambien, elimina


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso | Yes | string |
| destination_user_id | path | Usuario Destino | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 400 | Token de acceso invalido |
| 404 | Usuario destino inexistente |
| 408 | Usuario no es parte de la red |
| 412 | Solicitud no puede ser rechazada debido a su inexistencia. |

### /chat
---
##### ***GET***
**Summary:** Listado de conversaciones

**Description:** Posibilidad de acceder a todas las conversaciones realizadas.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |
| size | query | Cantidad de elementos en la respuesta. | No | integer |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Todas los chats existentes |
| 500 | Unexpected error |

##### ***POST***
**Summary:** Crear chat

**Description:** **Crear chat con dos o mas participantes.***


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |
| size | query | Cantidad de elementos en la respuesta. | No | integer |
| body | body | participantes | Yes | undefined |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Chat creado |
| 500 | Unexpected error |

### /chat/online
---
##### ***GET***
**Summary:** Listado de usuarios que están online.

**Description:** Posibilidad de ver los usuarios activos que forman parte de la red.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Todas los usuarios online pertenecientes a la red. |
| 500 | Unexpected error |

### /chat/{chat_id}
---
##### ***GET***
**Summary:** Obtener conversación

**Description:** **inserte simple descripcion aqui**, el orden es cronologico desde desde el mas nuevo al mas antiguo


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |
| destination_user_id | path | Usuario destino en la conversación. | Yes | string |
| size | query | Cantidad de mensajes a cargar del chat. | No | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Conversacion con user_id |
| 500 | Unexpected error |

##### ***POST***
**Summary:** Enviar mensaje

**Description:** **inserte simple descripcion aqui**


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |
| destination_user_id | path | Usuario destino en la conversación. | Yes | string |
| body | body | Puesto a dar de alta | No | undefined |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Mensaje enviado |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Eliminar conversacion

**Description:** Se permite eliminar conversacion con usuario.


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| access_token | header | Token de acceso | Yes | string |
| user_id | header | User id referido al token de acceso. | Yes | string |
| destination_user_id | path | Usuario destino en la conversación. | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Conversacion eliminada |
| 400 | No existe conversacion |
| 500 | Unexpected error |

### /user/{user_id}
---
##### ***GET***
**Summary:** Perfil del usuario indicado

**Description:** ** Descripcion **


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| user_id | path | Usuario id | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Perfil de usuario en cuestion |
| 400 | Usuario inexistente |
| 500 | Unexpected error |

##### ***PUT***
**Summary:** Modificar perfil

**Description:** ** Descripcion **


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| user_id | path | Usuario id | Yes | string |
| access_token | header | Token de acceso referido al user id | Yes | string |
| body | body | Informacion a modificar | Yes | undefined |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Perfil modificado. |
| 400 | Parametros invalidos |
| 500 | Unexpected error |

##### ***DELETE***
**Summary:** Eliminar perfil

**Description:** El usuario tiene el derecho de eliminarse de la plataforma


**Parameters**

| Name | Located in | Description | Required | Type |
| ---- | ---------- | ----------- | -------- | ---- |
| user_id | path | Usuario id | Yes | string |

**Responses**

| Code | Description |
| ---- | ----------- |
| 200 | Perfil eliminado |
| 500 | Unexpected error |
