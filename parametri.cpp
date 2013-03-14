#ifndef __BINNING_C
#define __BINNING_C

#include "leggi_binario_ALaDyn_fortran.h"



/* costruttore default - inizializza a zero per ora. Siccome tutto e' inizializzato a zero 
non puo' nemmeno calcolare le le dimensioni dei bin!
Verificare che non ci siano cose intelligenti da poter fare! */
Parametri :: Parametri()
{
	massa_particella_MeV = 0.;
	nbin = nbin_x = nbin_px = nbin_y = nbin_z = nbin_py = nbin_pz = nbin_E = nbin_theta = 100;
	xmin = pxmin = ymin = pymin = zmin = pzmin = thetamin = Emin = gammamin = 0.0;
	xmax = pxmax = ymax = pymax = zmax = pzmax = thetamax = Emax = gammamax = 1.0;
	ymin_b = ymax_b = pymin_b = pymax_b = zmin_b = zmax_b = pzmin_b = pzmax_b = gammamin_b = gammamax_b = true;
	xmin_b = xmax_b = pxmin_b = pxmax_b = Emin_b = Emax_b = thetamin_b = thetamax_b = true;
	nbin_b = true;
        nbin_E_b = nbin_theta_b = nbin_gamma_b = true;
	nbin_x_b = nbin_px_b = nbin_y_b = nbin_py_b = nbin_z_b = nbin_pz_b = true;
	fai_plot_xpx = fai_plot_Espec = fai_plot_Etheta = false;

	for (int i = 0; i < NPARAMETRI; i++) 
	{
		p_b[i] = true;
		p[i] = -1;
	}

	old_fortran_bin = false;
	endian_file = 0;
	endian_machine = is_big_endian();
	file_particelle_P = file_particelle_E = file_particelle_HI = file_particelle_LI = false;
	file_campi_Ex = file_campi_Ey = file_campi_Ez = file_campi_Bx = file_campi_By = file_campi_Bz = false;
	file_densita_elettroni = file_densita_protoni = file_densita_LI = file_densita_HI = false;
}



float Parametri :: dimmi_dimx()
{
	return (xmax - xmin) / static_cast <float> (nbin_x);
}
float Parametri :: dimmi_dimy()
{
	return (ymax - ymin) / static_cast <float> (nbin_y);
}
float Parametri :: dimmi_dimz()
{
	return (zmax - zmin) / static_cast <float> (nbin_z);
}
float Parametri :: dimmi_dimpx()
{
	return (pxmax - pxmin) / static_cast <float> (nbin_px);
}
float Parametri :: dimmi_dimpy()
{
	return (pymax - pymin) / static_cast <float> (nbin_py);
}
float Parametri :: dimmi_dimpz()
{
	return (pzmax - pzmin) / static_cast <float> (nbin_pz);
}
float Parametri :: dimmi_dimgamma()
{
	return (gammamax - gammamin) / static_cast <float> (nbin_gamma);
}
float Parametri :: dimmi_dimtheta()
{
	return (thetamax - thetamin) / static_cast <float> (nbin_theta);
}
float Parametri :: dimmi_dimE()
{
	return (Emax - Emin) / static_cast <float> (nbin_E);
}
float Parametri :: dimmi_dim(int colonna)
{
	if (colonna == 0)		return dimmi_dimx();
	else if (colonna == 1)	return dimmi_dimy();
	else if (colonna == 2)	return dimmi_dimz();
	else if (colonna == 3)	return dimmi_dimpx();
	else if (colonna == 4)	return dimmi_dimpy();
	else if (colonna == 5)	return dimmi_dimpz();
	else if (colonna == 6)	return dimmi_dimgamma();
	else if (colonna == 7)	return dimmi_dimtheta();
	else if (colonna == 8)	return dimmi_dimE();
	else return 1.0;
}


void Parametri :: leggi_endian_e_ncol(std::ifstream& file_dat)
{
	std::string riga_persa;
	int trascura, ndv, i_end;
	std::getline(file_dat,riga_persa);
	file_dat >> trascura; // 1� parametro
	file_dat >> trascura; // 2� parametro
	file_dat >> trascura; // 3� parametro
	file_dat >> trascura; // 4� parametro
	file_dat >> trascura; // 5� parametro
	file_dat >> trascura; // 6� parametro
	file_dat >> trascura; // 7� parametro
	file_dat >> trascura; // 8� parametro
	file_dat >> trascura; // 9� parametro
	file_dat >> trascura; // 10� parametro
	file_dat >> trascura; // 11� parametro
	file_dat >> trascura; // 12� parametro
	file_dat >> trascura; // 13� parametro
	file_dat >> trascura; // 14� parametro
	file_dat >> trascura; // 15� parametro
	file_dat >> trascura; // 16� parametro
	file_dat >> trascura; // 17� parametro
	file_dat >> ndv;	  // 18� parametro
	file_dat >> trascura; // 19� parametro
	file_dat >> i_end;	  // 20� parametro

	if (ndv == 4 || ndv == 6) p[WEIGHT] = 0;
	else if (ndv == 5 || ndv == 7) p[WEIGHT] = 1;
        else printf("Attenzione: valore illegale di ndv\n"), exit(-17);
        p[NCOLONNE] = ndv;
        p_b[NCOLONNE] = false;
	p_b[WEIGHT] = false;
	endian_file = (i_end-1);

}

void Parametri :: chiedi_numero_colonne()
{
	int ncolonne;
	std::cout << "Il file contiene 6 o 7 colonne? ";
	std::cin >> ncolonne;
	if (ncolonne==6) p[WEIGHT] = 0;
	else if (ncolonne==7) p[WEIGHT] = 1;
	else exit(-5);
	p_b[WEIGHT] = false;
}


void Parametri :: chiedi_endian_file()
{
	std::cout << "Il file e' little [x86] (0) o big [ppc] (1) endian? ";
	std::cin >> endian_file;
	if (endian_file != 1 && endian_file != 0) exit(-4);
}


void Parametri :: check_filename(const char *nomefile)
{
	if (nomefile[0] == 'P')
	{
		if (nomefile[1] == 'r')
		{
			if (nomefile[2] == 'p')
			{
				massa_particella_MeV = (float) MP_MEV;
				file_particelle_P = true;
			}
		}
		else if (nomefile[1] == 'd')
		{
			file_densita_protoni = true;
			sprintf (support_label,"pden");
		}
	}
	else if (nomefile[0] == 'H')
	{
		if (nomefile[1] == 'i')
		{
			if (nomefile[2] == 'd')
			{
				file_densita_HI = true;
				sprintf (support_label,"hiden");
			}
		}
	}
	else if (nomefile[0] == 'L')
	{
		if (nomefile[1] == 'i')
		{
			if (nomefile[2] == 'd')
			{
				file_densita_LI = true;
				sprintf (support_label,"liden");
			}
		}
	}
	else if (nomefile[0] == 'E')
	{
		if (nomefile[1] == 'l')
		{
			if (nomefile[2] == 'p')
			{
				massa_particella_MeV = (float) ME_MEV;
				file_particelle_E = true;
			}
		}
		else if (nomefile[1] == 'x')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_Ex = true;
				sprintf (support_label,"Ex");
			}
		}
		else if (nomefile[1] == 'y')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_Ey = true;
				sprintf (support_label,"Ey");
			}
		}
		else if (nomefile[1] == 'z')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_Ez = true;
				sprintf (support_label,"Ez");
			}
		}
		else if (nomefile[1] == 'd')
		{
			file_campi_Ez = true;
			sprintf (support_label,"eden");
		}
	}
	else if (nomefile[0] == 'B')
	{
		if (nomefile[1] == 'x')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_Bx = true;
				sprintf (support_label,"Bx");
			}
		}
		else if (nomefile[1] == 'y')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_By = true;
				sprintf (support_label,"By");
			}
		}
		else if (nomefile[1] == 'z')
		{
			if (nomefile[2] == 'f')
			{
				file_campi_Bz = true;
				sprintf (support_label,"Bz");
			}
		}
	}
	else
	{
		std::cout << "File non riconosciuto" << std::endl;
		exit(-15);
	}

}

void Parametri :: parse_command_line(int argc, const char ** argv)
{
	std::ifstream fileParametri;
	std::string nomefile;
	bool usa_file_parametri = false;
	bool failed_opening_file;
	bool do_not_ask_missing = false;
	for (int i = 2; i < argc; i++)	
		/************************************************************************
		We will iterate over argv[] to get the parameters stored inside.
		Note that we're starting on 1 because we don't need to know the
		path of the program, which is stored in argv[0], and the input file,
		which is supposed to be given as the first argument and so is in argv[1]
		************************************************************************/
	{

		if (std::string(argv[i]) == "-readParamsfromFile")
		{
			nomefile = std::string(argv[i+1]);
			usa_file_parametri = true;
			i++;
		}
		else if (std::string(argv[i]) == "-swap")
		{
			p[SWAP] = 1;
			p_b[SWAP] = false;
		}
		else if (std::string(argv[i]) == "-force_new")
		{
                        old_fortran_bin = false;
		}
		else if (std::string(argv[i]) == "-ncol")
		{
			int ncolumns = atoi(argv[i+1]);
			if (ncolumns == 6) p[WEIGHT] = 0;
			else if (ncolumns == 7) p[WEIGHT] = 1;
			p_b[WEIGHT] = false;
			i++;
		}
		else if (std::string(argv[i]) == "-dump_binary")
		{
			p[OUT_BINARY] = 1;
			p_b[OUT_BINARY] = false;
		}
		else if (std::string(argv[i]) == "-dump_propaga")
		{
			p[OUT_PROPAGA] = 1;
			p_b[OUT_PROPAGA] = false;
		}
		else if (std::string(argv[i]) == "-dump_csv")
		{
			p[OUT_CSV] = 1;
			p_b[OUT_CSV] = false;
		}
		else if (std::string(argv[i]) == "-parameters")
		{
			p[OUT_PARAMS] = 1;
			p_b[OUT_PARAMS] = false;
		}
		else if (std::string(argv[i]) == "-find_minmax")
		{
			p[FIND_MINMAX] = 1;
			p_b[FIND_MINMAX] = false;
		}
		else if (std::string(argv[i]) == "-do_binning")
		{
			p[DO_BINNING] = 1;
			p_b[DO_BINNING] = false;
		}
		else if (std::string(argv[i]) == "-xmin")
		{
			xmin = (float) atof(argv[i+1]);
			xmin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-xmax")
		{
			xmax = (float) atof(argv[i+1]);
			xmax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-ymin")
		{
			ymin = (float) atof(argv[i+1]);
			ymin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-ymax")
		{
			ymax = (float) atof(argv[i+1]);
			ymax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-zmin")
		{
			zmin = (float) atof(argv[i+1]);
			zmin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-zmax")
		{
			zmax = (float) atof(argv[i+1]);
			zmax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pxmin")
		{
			pxmin = (float) atof(argv[i+1]);
			pxmin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pxmax")
		{
			pxmax = (float) atof(argv[i+1]);
			pxmax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pymin")
		{
			pymin = (float) atof(argv[i+1]);
			pymin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pymax")
		{
			pymax = (float) atof(argv[i+1]);
			pymax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pzmin")
		{
			pzmin = (float) atof(argv[i+1]);
			pzmin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-pzmax")
		{
			pzmax = (float) atof(argv[i+1]);
			pzmax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-thetamin")
		{
			thetamin = (float) atof(argv[i+1]);
			thetamin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-thetamax")
		{
			thetamax = (float) atof(argv[i+1]);
			thetamax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-gammamin")
		{
			gammamin = (float) atof(argv[i+1]);
			gammamin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-gammamax")
		{
			gammamax = (float) atof(argv[i+1]);
			gammamax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-Emin")
		{
			Emin = (float) atof(argv[i+1]);
			Emin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-Emax")
		{
			Emax = (float) atof(argv[i+1]);
			Emax_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-plot_xpx")
		{
			fai_plot_xpx = 1;
		}
		else if (std::string(argv[i]) == "-plot_espec")
		{
			fai_plot_Espec = 1;
		}
		else if (std::string(argv[i]) == "-plot_etheta")
		{
			fai_plot_Etheta = 1;
		}
		else if (std::string(argv[i]) == "-nbin")
		{
			nbin = atoi(argv[i+1]);
			if (nbin_x_b) nbin_x = nbin;
			if (nbin_y_b) nbin_y = nbin;
			if (nbin_z_b) nbin_z = nbin;
			if (nbin_px_b) nbin_px = nbin;
			if (nbin_py_b) nbin_py = nbin;
			if (nbin_pz_b) nbin_pz = nbin;
			if (nbin_gamma_b) nbin_gamma = nbin;
			if (nbin_theta_b) nbin_theta = nbin;
			if (nbin_E_b) nbin_E = nbin;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinx")
		{
			nbin_x = atoi(argv[i+1]);
			nbin_x_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbiny")
		{
			nbin_y = atoi(argv[i+1]);
			nbin_y_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinz")
		{
			nbin_z = atoi(argv[i+1]);
			nbin_z_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinpx")
		{
			nbin_px = atoi(argv[i+1]);
			nbin_px_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinpy")
		{
			nbin_py = atoi(argv[i+1]);
			nbin_py_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinpz")
		{
			nbin_pz = atoi(argv[i+1]);
			nbin_pz_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbintheta")
		{
			nbin_theta = atoi(argv[i+1]);
			nbin_theta_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbingamma")
		{
			nbin_gamma = atoi(argv[i+1]);
			nbin_gamma_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-nbinE")
		{
			nbin_E = atoi(argv[i+1]);
			nbin_E_b = false;
			nbin_b = false;
			i++;
		}
		else if (std::string(argv[i]) == "-dontask")
		{
			do_not_ask_missing = true;
		}
	}


	std::string nomepar, evita, leggi;

	if (file_particelle_P || file_particelle_E || file_particelle_HI || file_particelle_LI)
	{
		if (usa_file_parametri)
		{
			fileParametri.open(nomefile.c_str());
			failed_opening_file = fileParametri.fail();
			if (failed_opening_file) 
			{
				std::cout << "Impossibile aprire il file " << nomefile << " contenente i parametri di binnaggio" << std::endl;
				exit(50);
			}
			while(!fileParametri.eof())
			{
				fileParametri >> nomepar >> evita >> leggi;
				if ((nomepar == "xmin" || nomepar == "XMIN") && xmin_b)
				{
					xmin = (float) std::atof(leggi.c_str());
					xmin_b = false;
				}
				else if ((nomepar == "xmax" || nomepar == "XMAX") && xmax_b)
				{
					xmax = (float) std::atof(leggi.c_str());
					xmax_b = false;
				}
				else if ((nomepar == "ymin" || nomepar == "YMIN") && ymin_b)
				{
					ymin = (float) std::atof(leggi.c_str());
					ymin_b = false;
				}
				else if ((nomepar == "ymax" || nomepar == "YMAX") && ymax_b)
				{
					ymax = (float) std::atof(leggi.c_str());
					ymax_b = false;
				}
				else if ((nomepar == "zmin" || nomepar == "ZMIN") && zmin_b)
				{
					zmin = (float) std::atof(leggi.c_str());
					zmin_b = false;
				}
				else if ((nomepar == "zmax" || nomepar == "ZMAX") && zmax_b)
				{
					zmax = (float) std::atof(leggi.c_str());
					zmax_b = false;
				}
				else if ((nomepar == "pxmin" || nomepar == "PXMIN") && pxmin_b)
				{
					pxmin = (float) std::atof(leggi.c_str());
					pxmin_b = false;
				}
				else if ((nomepar == "pxmax" || nomepar == "PXMAX") && pxmax_b)
				{
					pxmax = (float) std::atof(leggi.c_str());
					pxmax_b = false;
				}
				else if ((nomepar == "pymin" || nomepar == "PYMIN") && pymin_b)
				{
					pymin = (float) std::atof(leggi.c_str());
					pymin_b = false;
				}
				else if ((nomepar == "pymax" || nomepar == "PYMAX") && pymax_b)
				{
					pymax = (float) std::atof(leggi.c_str());
					pymax_b = false;
				}
				else if ((nomepar == "pzmin" || nomepar == "PZMIN") && pzmin_b)
				{
					pzmin = (float) std::atof(leggi.c_str());
					pzmin_b = false;
				}
				else if ((nomepar == "pzmax" || nomepar == "PZMAX") && pzmax_b)
				{
					pzmax = (float) std::atof(leggi.c_str());
					pzmax_b = false;
				}
				else if ((nomepar == "gammamin" || nomepar == "GAMMAMIN") && gammamin_b)
				{
					gammamin = (float) std::atof(leggi.c_str());
					gammamin_b = false;
				}
				else if ((nomepar == "gammamax" || nomepar == "GAMMAMAX") && gammamax_b)
				{
					gammamax = (float) std::atof(leggi.c_str());
					gammamax_b = false;
				}
				else if ((nomepar == "thetamin" || nomepar == "THETAMIN") && thetamin_b)
				{
					thetamin = (float) std::atof(leggi.c_str());
					thetamin_b = false;
				}
				else if ((nomepar == "thetamax" || nomepar == "THETAMAX") && thetamax_b)
				{
					thetamax = (float) std::atof(leggi.c_str());
					thetamax_b = false;
				}
				else if ((nomepar == "emin" || nomepar == "EMIN") && Emin_b)
				{
					Emin = (float) std::atof(leggi.c_str());
					Emin_b = false;
				}
				else if ((nomepar == "emax" || nomepar == "EMAX") && Emax_b)
				{
					Emax = (float) std::atof(leggi.c_str());
					Emax_b = false;
				}
				/*
				else
				{
				std::cout << "Parametro " << nomepar << " non riconosciuto." << std::endl;
				}
				*/
			}
			fileParametri.close();
		}
		if (p_b[FIND_MINMAX] && !do_not_ask_missing)
		{
			std::cout << "Vuoi cercare massimi e minimi? 0 per no, 1 per si': ";
			std::cin >> p[FIND_MINMAX];
			p_b[FIND_MINMAX] = false;
		}
		if (p_b[DO_BINNING] && !do_not_ask_missing)
		{
			std::cout << "Vuoi fare il binnaggio dei dati? 1 si', 0 no: ";
			std::cin >> p[DO_BINNING];
			p_b[DO_BINNING] = false;
		}
		if (p[DO_BINNING] == 1 && nbin_b)
		{
			std::cout << "Quanti bin per asse vuoi usare? (consiglio: 100): ";
			std::cin >> nbin;
			nbin_x = nbin_px = nbin_y = nbin_z = nbin_py = nbin_pz = nbin_E = nbin_theta = nbin;
		}
#ifdef ENABLE_DEBUG
		std::cout << "Dal file " << nomefile << " ho letto i seguenti estremi:" << std::endl;
		std::cout << "XMIN = " << xmin << std::endl;
		std::cout << "XMAX = " << xmax << std::endl;
		std::cout << "YMIN = " << ymin << std::endl;
		std::cout << "YMAX = " << ymax << std::endl;
		std::cout << "ZMIN = " << zmin << std::endl;
		std::cout << "ZMAX = " << zmax << std::endl;
		std::cout << "PXMIN = " << pxmin << std::endl;
		std::cout << "PXMAX = " << pxmax << std::endl;
		std::cout << "PYMIN = " << pymin << std::endl;
		std::cout << "PYMAX = " << pymax << std::endl;
		std::cout << "PZMIN = " << pzmin << std::endl;
		std::cout << "PZMAX = " << pzmax << std::endl;
		std::cout << "GAMMAMIN = " << gammamin << std::endl;
		std::cout << "GAMMAMAX = " << gammamax << std::endl;
		std::cout << "THETAMIN = " << thetamin << std::endl;
		std::cout << "THETAMAX = " << thetamax << std::endl;
		std::cout << "EMIN = " << Emin << std::endl;
		std::cout << "EMAX = " << Emax << std::endl;
#endif
		if (p_b[OUT_BINARY] && !do_not_ask_missing)
		{
			std::cout << "Vuoi l'output completo binario VTK? 1 si', 0 no: ";
			std::cin >> p[OUT_BINARY];
		}
		if (p_b[OUT_PROPAGA] && !do_not_ask_missing)
		{
			std::cout << "Vuoi l'output completo per Propaga? 1 si', 0 no: ";
			std::cin >> p[OUT_PROPAGA];
		}
		if (p_b[OUT_CSV] && !do_not_ask_missing)
		{
			std::cout << "Vuoi l'output completo CSV per Paraview? 1 si', 0 no: ";
			std::cin >> p[OUT_CSV];
		}
		if (p_b[OUT_PARAMS] && !do_not_ask_missing)
		{
			std::cout << "Vuoi l'output dei parametri contenuti nel file? 1 si', 0 no: ";
			std::cin >> p[OUT_PARAMS];
		}
	}
	fileParametri.close();
}


void Parametri :: leggi_interattivo()
{
	if (file_particelle_P || file_particelle_E || file_particelle_HI || file_particelle_LI)
	{
		std::cout << "Vuoi cercare massimi e minimi? 0 per no, 1 per si': ";
		std::cin >> p[FIND_MINMAX];
		std::cout << "Vuoi fare il binnaggio dei dati? 1 si', 0 no: ";
		std::cin >> p[DO_BINNING];
		if (p[DO_BINNING] == 1)
		{
			std::cout << "Vuoi fare il plot x-px? 0 per no, 1 per si': ";
			std::cin >> fai_plot_xpx;
			std::cout << "Vuoi fare il plot E-theta? 0 per no, 1 per si': ";
			std::cin >> fai_plot_Etheta;
			std::cout << "Vuoi fare lo spettro in energia? 0 per no, 1 per si': ";
			std::cin >> fai_plot_Espec;
			if (fai_plot_xpx)
			{
				if (xmin_b)
				{
					std::cout << "xmin = ";
					std::cin >> xmin;
					xmin_b = false;
				}
				if (xmax_b)
				{
					std::cout << "xmax = ";
					std::cin >> xmax;
					xmax_b = false;
				}
				if (nbin_x_b)
				{
					std::cout << "nbin_x = ";
					std::cin >> nbin_x;
					nbin_x_b = false;
				}
			}
			if (fai_plot_Etheta)
			{
				if (thetamin_b)
				{
					std::cout << "thetamin = ";
					std::cin >> thetamin;
					thetamin_b = false;
				}
				if (thetamax_b)
				{
					std::cout << "thetamax = ";
					std::cin >> thetamax;
					thetamax_b = false;
				}
				if (nbin_theta_b)
				{
					std::cout << "nbin_theta = ";
					std::cin >> nbin_theta;
					nbin_theta_b = false;
				}
			}
			if (fai_plot_Etheta || fai_plot_Espec)
			{
				if (Emin_b)
				{
					std::cout << "Emin = ";
					std::cin >> Emin;
					Emin_b = false;
				}
				if (Emax_b)
				{
					std::cout << "Emax = ";
					std::cin >> Emax;
					Emax_b = false;
				}
				if (nbin_E_b)
				{
					std::cout << "nbin_E = ";
					std::cin >> nbin_E;
					nbin_E_b = false;
				}
			}
		}
#ifdef ENABLE_DEBUG
		std::cout << "Ora ho i seguenti estremi:" << std::endl;
		std::cout << "XMIN = " << xmin << std::endl;
		std::cout << "XMAX = " << xmax << std::endl;
		std::cout << "YMIN = " << ymin << std::endl;
		std::cout << "YMAX = " << ymax << std::endl;
		std::cout << "ZMIN = " << zmin << std::endl;
		std::cout << "ZMAX = " << zmax << std::endl;
		std::cout << "PXMIN = " << pxmin << std::endl;
		std::cout << "PXMAX = " << pxmax << std::endl;
		std::cout << "PYMIN = " << pymin << std::endl;
		std::cout << "PYMAX = " << pymax << std::endl;
		std::cout << "PZMIN = " << pzmin << std::endl;
		std::cout << "PZMAX = " << pzmax << std::endl;
		std::cout << "GAMMAMIN = " << gammamin << std::endl;
		std::cout << "GAMMAMAX = " << gammamax << std::endl;
		std::cout << "THETAMIN = " << thetamin << std::endl;
		std::cout << "THETAMAX = " << thetamax << std::endl;
		std::cout << "EMIN = " << Emin << std::endl;
		std::cout << "EMAX = " << Emax << std::endl;
#endif		
		std::cout << "Vuoi l'output completo binario VTK? 1 si', 0 no: ";
		std::cin >> p[OUT_BINARY];
		std::cout << "Vuoi l'output completo per Propaga? 1 si', 0 no: ";
		std::cin >> p[OUT_PROPAGA];
		std::cout << "Vuoi l'output completo CSV per Paraview? 1 si', 0 no: ";
		std::cin >> p[OUT_CSV];
		std::cout << "Vuoi l'output dei parametri contenuti nel file? 1 si', 0 no: ";
		std::cin >> p[OUT_PARAMS];
	}

}



bool Parametri :: check_parametri()
{
	bool test = true;
	if ( p[SWAP]     != 0 && p[SWAP]       != 1 )		// check swap o non-swap
	{
		printf("Attenzione: modalita` swap non definita\n");
		test = false;
	}
	if ( (file_particelle_P || file_particelle_E) && p[WEIGHT]     != 0 && p[WEIGHT]     != 1 )	// check leggi_particelle: weight o non-weight
	{
		printf("Attenzione: modalita` weight non definita\n");
		test = false;
	}
	if ( (file_particelle_P || file_particelle_E) && p[OUT_CSV]  != 0 && p[OUT_CSV]  != 1 )	// check leggi_particelle: out-ascii o non-out-ascii
	{
		printf("Attenzione: output csv non definito\n");
		test = false;
	}
	if ( (file_particelle_P || file_particelle_E) && p[OUT_PROPAGA]  != 0 && p[OUT_PROPAGA]  != 1 )	// check leggi_particelle: out-ascii o non-out-ascii
	{
		printf("Attenzione: output ppg non definito\n");
		test = false;
	}
	if ( (file_particelle_P || file_particelle_E) && p[OUT_BINARY] != 0 && p[OUT_BINARY] != 1  )
	{
		printf("Attenzione: output binario non definito\n");
		test = false;
	}
	if ( xmin >= xmax )
	{
		printf("Attenzione: xmin > xmax\n");
		test = false;
	}
	if ( ymin >= ymax ) 
	{
		printf("Attenzione: ymin > ymax\n");
		test = false;
	}
	if ( zmin >= zmax )
	{
		printf("Attenzione: zmin > zmax\n");
		test = false;
	}
	if (pxmin >= pxmax)
	{
		printf("Attenzione: pxmin > pxmax\n");
		test = false;
	}
	if (pymin >= pymax)
	{
		printf("Attenzione: pymin > pymax\n");
		test = false;
	}
	if (pzmin >= pzmax)
	{
		printf("Attenzione: pzmin > pzmax\n");
		test = false;
	}
	if ( nbin_x <= 0 )
	{
		printf("Attenzione: nbin_x < 0\n");
		test = false;
	}
	if ( nbin_y <= 0 )
	{
		printf("Attenzione: nbin_y < 0\n");
		test = false;
	}
	if ( nbin_z <= 0 )
	{
		printf("Attenzione: nbin_z < 0\n");
		test = false;
	}
	if ( nbin_px <= 0 )
	{
		printf("Attenzione: nbin_px < 0\n");
		test = false;
	}
	if ( nbin_py <= 0 )
	{
		printf("Attenzione: nbin_py < 0\n");
		test = false;
	}
	if (nbin_pz <= 0)
	{
		printf("Attenzione: nbin_pz < 0\n");
		test = false;
	}
	return test;
}


void Parametri :: organizza_minimi_massimi()
{
	minimi[0] = xmin;
	minimi[1] = ymin;
	minimi[2] = zmin;
	minimi[3] = pxmin;
	minimi[4] = pymin;
	minimi[5] = pzmin;
	minimi[6] = gammamin;
	minimi[7] = thetamin;
	minimi[8] = Emin;

	massimi[0] = xmax;
	massimi[1] = ymax;
	massimi[2] = zmax;
	massimi[3] = pxmax;
	massimi[4] = pymax;
	massimi[5] = pzmax;
	massimi[6] = gammamax;
	massimi[7] = thetamax;
	massimi[8] = Emax;

#ifdef ENABLE_DEBUG
	std::cout << "---- organizza_minimi_massimi() -----" << std::endl;
	std::cout << "Hai scritto Emin = "<< Emin << "  Emax = "<< Emax << std::endl;
	std::cout << "Hai scritto minimi[8] = "<< minimi[8] << "  massimi[8] = "<< massimi[8] << std::endl;
#endif
}



bool Parametri :: incompleto()
{
	bool test=true;
	//	if (!xmin_b && !xmax_b && !pxmin_b && !pxmax_b && !ymin_b && !ymax_b && !pymin_b && !pymax_b && !zmin_b && !zmax_b && !pzmin_b && !pzmax_b && 
	//		!Emin_b && !Emax_b && !nbin_x_b && !nbin_y_b && !nbin_z_b && !nbin_px_b && !nbin_py_b && !nbin_pz_b && !nbin_E_b)  test = false;
	//	if (!gammamin_b && !gammamax_b && !thetamin_b && !thetamax_b && !nbin_theta_b && !nbin_gamma_b && !test) test = false;

	test=false;
	return test;
}


#endif
