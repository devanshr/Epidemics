PrintBuildConfiguration()

-----------------------------------------------------------------
-- define Home-Directories
----------------------------------------------------------------
ug4_home        = ug_get_root_path().."/"

--common_scripts  = app_home.."scripts/"
--geom_home       = app_home.."geometry/"

-----------------------------------------------------------------


--Load Parameters
local pars = "parameters.lua"

local parmfileloaded= false
if(pfile ~= "") then
	local file = assert(loadfile(pars))
	file()
	parmfileloaded = true
end
if parmfileloaded == false then
	print("Parameter file could not be loaded")
end

--Start of parameter, constants and initial values definitions

ht=0.3
hx=0.3
t_end=0.6
t_start=0
r1=10
r2=1
r3=0
r4=0
r5=0
v1=10
v2=10
v3=0
v4=0
v5=0
kappa=0.1
theta=0.00984
qq=1
pp=1
diffusion=0
alpha=parameters.alpha:get_value_as_double()

initial_vars=InitialValueManager()

initial_vars:set_hx(hx)
initial_vars:set_ht(ht)
initial_vars:set_t_end(t_end)
initial_vars:set_t_start(t_start)
initial_vars:set_r1(r1)
initial_vars:set_r2(r2)
initial_vars:set_r3(r3)
initial_vars:set_r4(r4)
initial_vars:set_r5(r5)

initial_vars:set_v1(v1)
initial_vars:set_v2(v2)
initial_vars:set_v3(v3)
initial_vars:set_v4(v4)
initial_vars:set_v5(v5)
seird_model=SEIRD_PDE(alpha,kappa,theta,qq,pp,diffusion)
RunSEIRDPDE(seird_model,initial_vars,"./","output")
							