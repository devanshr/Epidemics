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

h=0.125
t_start=0
t_end=66
init_susceptibles=820000
init_exposed=1755
init_infected=0
init_recovered=0
init_deaths=1
kappa=0.1
theta=0.01
qq=4
pp=10
alpha=parameters.alpha:get_value_as_double()


			seird_model=SEIRD(alpha,kappa,theta,qq,pp)
			RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
									