/*
 * Copyright (C) 2019 Inan Evin - Thanks to the contributions of Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "common.glh"
#include "lights.glh"

varying vec2 texCoord0;

#if defined(VS_BUILD)
Layout(0) attribute vec3 position;
Layout(1) attribute vec2 texCoord;
Layout(4) attribute mat4 mvp;

void main()
{
    gl_Position = vec4(position, 1.0) * mvp;
    texCoord0 = texCoord;
}

#elif defined(FS_BUILD)

uniform sampler2D diffuse;
out vec4 fragColor;
uniform Light ambientLight;

void main()
{
	// ambient
    vec3 ambient = ambientLight.intensity * ambientLight.color;    
	
	// Final light color
	vec3 lightResult = ambient;
	
	fragColor = texture2D(diffuse, texCoord0) * vec4(lightResult, 1.0);
}
#endif
