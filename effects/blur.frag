#version 130

uniform sampler2D texture;
uniform float radius;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float total = 0.0;

    for (float x = -radius; x <= radius; x++) {
        for (float y = -radius; y <= radius; y++) {
            float weight = exp(-(x*x + y*y) / (2.0 * radius * radius));
            color += texture2D(texture, texCoord + vec2(x, y) / vec2(900.0, 600.0)) * weight;  // adapte à ta résolution
            total += weight;
        }
    }

    gl_FragColor = color / total;
}
