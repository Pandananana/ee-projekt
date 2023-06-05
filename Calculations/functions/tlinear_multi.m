function output = tlinear_multi(equation,left_side_variables,right_side_variables,point_variable,point_vaue)
% Linearize multivariable function at operating point

% left_side_variables has to be all non-fixed variables on left side of
% equation

% right_side_variables has to be all non-fixed variables on right side of
% equation

% If function needs to be evaluated at a specific operating point, then
% write the point variable(s) and their resulting values. Use arrays if
% multiple points with multiple values

gL = gradient(lhs(equation),left_side_variables);
gR = gradient(rhs(equation),right_side_variables);
left_tot=[];
for i=1:length(left_side_variables)
    left_sym=sym(strcat('Delta_',string(left_side_variables(i))));
    left_tot=[left_tot,left_sym];
end
right_tot=[];
for i=1:length(right_side_variables)
    right_sym=sym(strcat('Delta_',string(right_side_variables(i))));
    right_tot=[right_tot,right_sym];
end
equation_linear=sum(gL.'.*left_tot)==sum(gR.'.*right_tot);
output=vpa(equation_linear,5);
if nargin >= 5
    output = vpa(subs(output,point_variable,point_vaue),5);
end
end