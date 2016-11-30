#include <stdio.h>
#include <string.h>

int main() {
	char *source = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	size_t source_length = strlen(source);
	size_t i;
	FILE *out;

	out = popen("gcc -o a.out -xc -", "w");

	fprintf(out, "#include <stdio.h>\n#include <inttypes.h>\nint main() {\n");
	fprintf(out, "\tuint8_t a[300];\n\tint i = 0;\n\n\t");
	fprintf(out, "for(i = 0; i < sizeof(a); i++) { a[i] = 0; } i = 0;\n\n\t");

	for(i = 0; i < source_length; i++) {
		if(source[i] == '+') {
			fprintf(out, "a[i]++;");
		} else if(source[i] == '-') {
			fprintf(out, "a[i]--;");
		} else if(source[i] == '<') {
			fprintf(out, "i--;");
		} else if(source[i] == '>') {
			fprintf(out, "i++;");
		} else if(source[i] == '[') {
			fprintf(out, "while(a[i]) {");
		} else if(source[i] == ']') {
			fprintf(out, "}");
		} else if(source[i] == '.') {
			fprintf(out, "putchar(a[i]);");
		} else if(source[i] == ',') {
			fprintf(out, "a[i] = getchar();");
		}
	}

	fprintf(out, "\n\n}\n");
}
