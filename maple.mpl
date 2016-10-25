nsoksAUX := proc(n, k, maxsq:=infinity)
local minTs, maxTs, trialSquare, val, r;
    maxTs := isqrt(n-k+1);
    if k = 1 then
        if maxTs^2 = n then
            return {[maxTs]};
        else return {};
        end if;
    end if;
    if maxTs^2 > n-k+1 then
        maxTs := maxTs-1;
    end if;
    maxTs := min(maxTs,maxsq);
    minTs := isqrt(iquo(n,k,'r') + `if`(r<>0,1,0));
    if k*minTs^2 < n then
        minTs := minTs+1;
    end if;
    if minTs > maxTs then return {} end if;
    { seq(seq([val[],trialSquare]
              , val = procname(n-trialSquare^2,k-1,trialSquare))
          , trialSquare = minTs .. maxTs) };
end proc:

nsoks := proc(nn,kk)
local kkk,i,res,nres,ii;
# make the result a list
res := [op(`union`(seq(nsoksAUX(nn,kkk), kkk=1..kk)))];
nres := nops(res);
# if an element of the result has less than kk elements,
# then replace it with an element with the right number of zeros
for i from 1 to nres do
   if nops(res[i])<>kk then res := subsop(i=[seq(0,ii=1..kk-nops(res[i])),op(res[i])],res): fi;
od;
res;
end proc: