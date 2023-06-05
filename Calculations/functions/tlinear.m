function output = tlinear(equation,output,input,point_variable,point_vaue)
% Linearize multivariable function at operating point

% Output has to be a single symbolic variable

% Input can be multiple symbolic variables in an array

% If function needs to be evaluated at a specific operating point, then
% write the point variable(s) and their resulting values. Use arrays if
% multiple points with multiple values

equation=isolate(equation,output);
gL = gradient(lhs(equation),output);
gR = gradient(rhs(equation),input);
output_tot=[];
for i=1:length(output)
    output_sym=sym(strcat('Delta_',string(output(i))));
    output_tot=[output_tot,output_sym];
end
input_tot=[];
for i=1:length(input)
    input_sym=sym(strcat('Delta_',string(input(i))));
    input_tot=[input_tot,input_sym];
end
equation_linear=sum(gL.'.*output_tot)==sum(gR.'.*input_tot);
output=vpa(equation_linear,5);
if nargin >= 5
    output = vpa(subs(output,point_variable,point_vaue),5);
end
end