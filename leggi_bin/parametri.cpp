
#include "leggi_binario_ALaDyn_fortran.h"
#include "swap_tools.h"


/* costruttore default - inizializza a zero per ora. Siccome tutto e' inizializzato a zero
non puo' nemmeno calcolare le le dimensioni dei bin!
Verificare che non ci siano cose intelligenti da poter fare! */
Parametri::Parametri()
{
  nparams = NUMERO_PARAMETRI_FILE_DAT;
  intpar.resize(NUMERO_PARAMETRI_FILE_DAT, 0);
  realpar.resize(NUMERO_PARAMETRI_FILE_DAT, 0.0);
  header_size_bytes = 0;
  subsample = 1;
  span = 5;
  ncpu_x = ncpu_y = ncpu_z = ncpu = 0;
  nptot = ndv = 0;
  is_2d_sim = false;
  npx = npy = npz = npx_per_cpu = npy_per_cpu = npz_per_cpu = 0;
  npx_ricampionati = npy_ricampionati = npz_ricampionati = npx_ricampionati_per_cpu = npy_ricampionati_per_cpu = npz_ricampionati_per_cpu = 0;
  fattore_ricampionamento = 0;
  endianness = 0;
  file_version = 1;
  fixed_aladyn_version = false;
  multifile = false;
  stretched_grid = true;
  stretched_along_x = 1;
  massa_particella_MeV = 0.;
  nbin = nbin_x = nbin_px = nbin_y = nbin_py = nbin_z = nbin_pz = nbin_w = nbin_ch = nbin_E = nbin_gamma = nbin_theta = nbin_thetaT = nbin_ty = nbin_tz = NUMBER_OF_BIN_BY_DEFAULT;
  tnow = 0.0;
  xmin = pxmin = ymin = pymin = zmin = pzmin = wmin = chmin = thetamin = thetaTmin = Emin = gammamin = 0.0;
  xmax = pxmax = ymax = pymax = zmax = pzmax = wmax = chmax = thetamax = thetaTmax = Emax = gammamax = 1.0;
  tymin = tzmin = -1.0;
  tymax = tzmax = 1.0;
  ymin_b = ymax_b = pymin_b = pymax_b = zmin_b = zmax_b = pzmin_b = pzmax_b = wmin_b = wmax_b = chmin_b = chmax_b = gammamin_b = gammamax_b = true;
  xmin_b = xmax_b = pxmin_b = pxmax_b = Emin_b = Emax_b = thetaTmin_b = thetaTmax_b = thetamin_b = thetamax_b = tymin_b = tymax_b = tzmin_b = tzmax_b = true;
  nbin_b = true;
  nbin_E_b = nbin_theta_b = nbin_thetaT_b = nbin_ty_b = nbin_tz_b = nbin_gamma_b = true;
  nbin_x_b = nbin_px_b = nbin_y_b = nbin_py_b = nbin_z_b = nbin_pz_b = true;
  fai_plot_wspec = fai_plot_chspec = fai_plot_Espec = fai_plot_thetaspec = fai_plot_thetaTspec = fai_plot_Etheta = fai_plot_EthetaT = false;
  fai_plot_xy = fai_plot_xz = fai_plot_yz = fai_plot_xpx = fai_plot_xpy = fai_plot_xpz = fai_plot_ypx = false;
  fai_plot_ypy = fai_plot_ypz = fai_plot_zpx = fai_plot_zpy = fai_plot_zpz = fai_plot_pxpy = fai_plot_pxpz = fai_plot_pypz = fai_plot_xw = fai_plot_rcf = false;
  overwrite_weight = false;
  overwrite_charge = false;
  overwrite_weight_value = 1.0;
  overwrite_charge_value = 1.0;
  do_not_ask_missing = false;
  memset(&support_label[0], 0, sizeof(support_label));
  memset(&minimi[0], 0, sizeof(float) * sizeof(minimi));
  memset(&massimi[0], 0, sizeof(float) * sizeof(massimi));

  last_cpu = MAX_NUMBER_OF_CPUS;    // il tool funziona quindi per un ncpu_max, attualmente, pari a 32768

  for (int i = 0; i < NPARAMETRI; i++)
  {
    p_b[i] = true;
    p[i] = -1;
  }

  endian_file = 0;
  endian_machine = is_big_endian();
  file_spaziofasi = false;
  file_griglia = false;
  file_particelle_P = file_particelle_E = file_particelle_HI = file_particelle_LI = file_particelle_generic_ion = false;
  file_campi_Ex = file_campi_Ey = file_campi_Ez = file_campi_Bx = file_campi_By = file_campi_Bz = false;
  file_correnti_Jx = file_correnti_Jy = file_correnti_Jz = false;
  file_densita_elettroni = file_densita_protoni = file_densita_LI = file_densita_HI = file_densita_generic_ion = file_densita_driver = false;
  file_densita_energia_griglia_elettroni = file_densita_energia_griglia_protoni = file_densita_energia_griglia_HI = file_densita_energia_griglia_LI = file_densita_energia_griglia_generic_ion = false;
}



float Parametri::dimmi_dimx()
{
  return (xmax - xmin) / static_cast <float> (nbin_x);
}
float Parametri::dimmi_dimy()
{
  return (ymax - ymin) / static_cast <float> (nbin_y);
}
float Parametri::dimmi_dimz()
{
  return (zmax - zmin) / static_cast <float> (nbin_z);
}
float Parametri::dimmi_dimty()
{
  return (tymax - tymin) / static_cast <float> (nbin_ty);
}
float Parametri::dimmi_dimtz()
{
  return (tzmax - tzmin) / static_cast <float> (nbin_tz);
}
float Parametri::dimmi_dimpx()
{
  return (pxmax - pxmin) / static_cast <float> (nbin_px);
}
float Parametri::dimmi_dimpy()
{
  return (pymax - pymin) / static_cast <float> (nbin_py);
}
float Parametri::dimmi_dimpz()
{
  return (pzmax - pzmin) / static_cast <float> (nbin_pz);
}
float Parametri::dimmi_dimw()
{
  return (wmax - wmin) / static_cast <float> (nbin_w);
}
float Parametri::dimmi_dimch()
{
  return (chmax - chmin) / static_cast <float> (nbin_ch);
}
float Parametri::dimmi_dimgamma()
{
  return (gammamax - gammamin) / static_cast <float> (nbin_gamma);
}
float Parametri::dimmi_dimtheta()
{
  return (thetamax - thetamin) / static_cast <float> (nbin_theta);
}
float Parametri::dimmi_dimthetaT()
{
  return (thetaTmax - thetaTmin) / static_cast <float> (nbin_thetaT);
}
float Parametri::dimmi_dimE()
{
  return (Emax - Emin) / static_cast <float> (nbin_E);
}


int Parametri::dimmi_nbin(int colonna)
{
  if (colonna == 0)       return nbin_x;
  else if (colonna == 1)  return nbin_y;
  else if (colonna == 2)  return nbin_z;
  else if (colonna == 3)  return nbin_px;
  else if (colonna == 4)  return nbin_py;
  else if (colonna == 5)  return nbin_pz;
  else if (colonna == 6)  return nbin_gamma;
  else if (colonna == 7)  return nbin_theta;
  else if (colonna == 8)  return nbin_E;
  else if (colonna == 9)  return nbin_thetaT;
  else if (colonna == 10) return nbin_ty;
  else if (colonna == 11) return nbin_tz;
  else if (colonna == 12) return nbin_w;
  else if (colonna == 13) return nbin_ch;
  else return 120;
}



float Parametri::dimmi_dim(int colonna)
{
  if (colonna == 0)       return dimmi_dimx();
  else if (colonna == 1)  return dimmi_dimy();
  else if (colonna == 2)  return dimmi_dimz();
  else if (colonna == 3)  return dimmi_dimpx();
  else if (colonna == 4)  return dimmi_dimpy();
  else if (colonna == 5)  return dimmi_dimpz();
  else if (colonna == 6)  return dimmi_dimgamma();
  else if (colonna == 7)  return dimmi_dimtheta();
  else if (colonna == 8)  return dimmi_dimE();
  else if (colonna == 9)  return dimmi_dimthetaT();
  else if (colonna == 10) return dimmi_dimty();
  else if (colonna == 11) return dimmi_dimtz();
  else if (colonna == 12) return dimmi_dimw();
  else if (colonna == 13) return dimmi_dimch();
  else return 1.0;
}



void Parametri::leggi_parametri_da_file_bin(const char * filename)
{
  std::FILE * file_in = NULL;
  int fortran_buff;
  size_t fread_size = 0;

  file_in = fopen(filename, "rb");
  if (file_in == NULL) std::cout << "Unable to open file!" << std::endl;
  else std::cout << "File opened to read parameters!" << std::endl;

  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);
  fread_size += std::fread(&nparams, sizeof(int), 1, file_in);
  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);

  if (p[SWAP]) swap_endian_i(&nparams, 1);

  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);
  fread_size += std::fread(&intpar[0], sizeof(int), nparams, file_in);
  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);
  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);
  fread_size += std::fread(&realpar[0], sizeof(float), nparams, file_in);
  fread_size += std::fread(&fortran_buff, sizeof(int), 1, file_in);

  if (p[SWAP]) swap_endian_i(intpar);
  if (p[SWAP]) swap_endian_f(realpar);

  fclose(file_in);

  /* overwrite default with good values */
  ncpu_x = 1;
  ncpu_y = intpar[0];
  ncpu_z = intpar[1];
  npx_ricampionati_per_cpu = intpar[2];
  npx = intpar[3];
  npy = intpar[4];
  npy_ricampionati_per_cpu = intpar[5];
  npz = intpar[6];
  npz_ricampionati_per_cpu = intpar[7];
  nptot = (long long int) intpar[16];
  ndv = intpar[17];
  file_version = intpar[18];
  endianness = intpar[19];
  tnow = realpar[0];  //tempo dell'output
  xmin = realpar[1];  //estremi della griglia
  xmax = realpar[2];  //estremi della griglia
  ymin = realpar[3];  //estremi della griglia
  ymax = realpar[4];  //estremi della griglia
  zmin = realpar[5];  //estremi della griglia
  zmax = realpar[6];  //estremi della griglia

  is_2d_sim = ((ndv == 4 || ndv == 5) && file_version < 3) || (ndv == 6 && file_version >= 3);

  header_size_bytes = (7 + nparams) * sizeof(int) + nparams * sizeof(float);
  if (fread_size != header_size_bytes) std::cout << "error: header size is different than expected" << std::endl << std::flush;
}



void Parametri::leggi_file_dat(std::ifstream& file_dat)
{
  std::string riga_persa;
  int fattore_ricampionamento;
  //  int discriminante_versione_file;
  float coord;
  std::getline(file_dat, riga_persa); // per leggere la riga Integer parameters


  for (int i = 0; i < nparams; i++)
  {
    file_dat >> intpar[i];
    if (file_dat.fail())
    {
      file_dat.clear();
      std::cout << "Unable to parse int_par #" << i + 1 << std::endl;
      if (i <= 7 || i >= 16)
      {
        std::cout << "Bad error; please fix the .dat file if possibile and then re-run the program" << std::endl;
        exit(-77);
      }
      file_dat.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
  }
  std::getline(file_dat, riga_persa); // per pulire i caratteri rimanenti sull'ultima riga degli interi
  std::getline(file_dat, riga_persa); // per leggere la riga Real parameters
  for (int i = 0; i < nparams; i++)
  {
    file_dat >> realpar[i];
    if (file_dat.fail())
    {
      file_dat.clear();
      std::cout << "Unable to parse real_par #" << i + 1 << std::endl;
      if (i <= 6)
      {
        std::cout << "Bad error; please fix the .dat file if possibile and then re-run the program" << std::endl;
        exit(-77);
      }
      file_dat.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
  }

  if (!fixed_aladyn_version) {
    file_version = intpar[18];
    // compatibility fixes (sometimes aladyn versions were defined as negatives with this convention)
    if (file_version == -1) file_version = 2;
    if (file_version == -2) file_version = 3;
  }

  std::cout << "Parsing an ALaDyn file versioned as v" << file_version << std::endl;

  if (file_version == 1) {

    /*
    real_par(1:20) =(/tnow,xmin,xmax,ymin,ymax,zmin,zmax,w0_x,w0_y,&
    n_over_nc,a0,lam0,E0,ompe,targ_in,targ_end,&
    gam0,nb_over_np,b_charge,vbeam/)

    int_par(1:20) = (/npe_loc,npe_zloc,nx,nxh,ny1,loc_nyc_max,nz1,loc_nzc_max,jump,iby,iform,&
    model_id,dmodel_id,nsp,curr_ndim,np_per_cell(1),&
    LPf_ord,der_ord,file_version,i_end/)
    */

    ncpu_y = intpar[0];
    ncpu_z = intpar[1];
    ncpu_x = 1;
    last_cpu = ncpu_x * ncpu_y * ncpu_z;
    ncpu = ncpu_x * ncpu_y * ncpu_z;

    endianness = intpar[19];
    tnow = realpar[0];
    xmin = realpar[1];
    xmax = realpar[2];
    ymin = realpar[3];
    ymax = realpar[4];
    zmin = realpar[5];
    zmax = realpar[6];

    if (file_griglia) {
      npx = intpar[2];
      npx_ricampionati = intpar[3];
      npx_per_cpu = npx / ncpu_x;
      fattore_ricampionamento = (int)(npx / npx_ricampionati);
      npy_ricampionati = intpar[4];
      npy_per_cpu = intpar[5];
      npy = npy_ricampionati * fattore_ricampionamento;
      npz_ricampionati = intpar[6];
      npz_per_cpu = intpar[7];
      if (npz_ricampionati > 1) npz = npz_ricampionati * fattore_ricampionamento;
      else npz = npz_ricampionati;
      npx_ricampionati_per_cpu = npx_ricampionati / ncpu_x;
      npy_ricampionati_per_cpu = npy_ricampionati / ncpu_y;
      npz_ricampionati_per_cpu = npz_ricampionati / ncpu_z;
      header_size_bytes = (nparams + 1) * sizeof(int) + nparams * sizeof(float) + 6 * sizeof(int); // there are 6 fortran buffers: two around nparams, two around intpars and two around realpars
    }
    else {
      nptot = (long long int) intpar[16];
      ndv = intpar[17];
      header_size_bytes = (nparams + 1) * sizeof(int) + nparams * sizeof(float);
    }
  }
  else if (file_version == 2) {
    endianness = intpar[19];

    tnow = realpar[0];
    xmin = realpar[1];
    xmax = realpar[2];
    ymin = realpar[3];
    ymax = realpar[4];
    zmin = realpar[5];
    zmax = realpar[6];

    if (file_griglia) {

      /*
      real_par(1:20) = (/ tnow, xmin, xmax, ymin, ymax, zmin, zmax, w0_x, w0_y, &
      n_over_nc, a0, lam0, E0, ompe, targ_in, targ_end, &
      gam0, nb_over_np, b_charge, vbeam / )

      int_par(1:20) = (/ npe_yloc, npe_zloc, npe_xloc, &
      nx1, ny1, loc_nyc_max, nz1, loc_nzc_max, jump, iby, iform, &
      model_id, dmodel_id, nsp, curr_ndim, mp_per_cell(1), &
      LPf_ord, der_ord, file_version, i_end / )
      */

      ncpu_y = intpar[0];
      ncpu_z = intpar[1];
      ncpu_x = intpar[2];
      ncpu = ncpu_x * ncpu_y * ncpu_z;
      last_cpu = ncpu_x * ncpu_y * ncpu_z;

      npx_ricampionati = intpar[3];
      npy_ricampionati = intpar[4];
      npy_per_cpu = intpar[5];
      npz_ricampionati = intpar[6];
      npz_per_cpu = intpar[7];
      fattore_ricampionamento = intpar[8];
      npx_ricampionati_per_cpu = npx_ricampionati / ncpu_x;
      npy_ricampionati_per_cpu = npy_per_cpu / fattore_ricampionamento;
      npz_ricampionati_per_cpu = npz_per_cpu / fattore_ricampionamento;
      npx = npx_ricampionati * fattore_ricampionamento;
      npy = npy_ricampionati * fattore_ricampionamento;
      if (npz_ricampionati > 1) npz = npz_ricampionati * fattore_ricampionamento;
      else npz = npz_ricampionati;
      npx_per_cpu = npx / ncpu_x;
      header_size_bytes = (nparams + 1 + 6) * sizeof(int) + nparams * sizeof(float); // +1 for n_par, +6 for fortran buffers (2 around nparams, 2 around intpars, 2 around realpars)
    }

    else {
      nptot = (long long int) intpar[16];
      ndv = intpar[17];
      header_size_bytes = (nparams + 1) * sizeof(int) + nparams * sizeof(float);
    }

  }
  else if (file_version == 3) {
    tnow = realpar[0];
    xmin = realpar[1];
    xmax = realpar[2];
    ymin = realpar[3];
    ymax = realpar[4];
    zmin = realpar[5];
    zmax = realpar[6];

    header_size_bytes = (nparams + 1) * sizeof(int) + nparams * sizeof(float);
    endianness = intpar[19];

    if (file_griglia) {
      /*
      real_par(1:20) =(/tnow,xmin,xmax,ymin,ymax,zmin,zmax,w0_x,w0_y,&
      n_over_nc,a0,lam0,E0,ompe,targ_in,targ_end,&
      gam0,nb_over_np,b_charge,vbeam/)

      int_par(1:20) = (/npe_loc,npe_zloc,npe_xloc,&
      nx1,ny1,loc_nyc_max,nz1,loc_nzc_max,jump,iby,iform,&
      model_id,dmodel_id,nsp,curr_ndim,mp_per_cell(1),&
      LPf_ord,der_ord,file_version,i_end/)
      */

      ncpu_y = intpar[0];
      ncpu_z = intpar[1];
      ncpu_x = intpar[2];
      ncpu = ncpu_x * ncpu_y * ncpu_z;
      last_cpu = ncpu_x * ncpu_y * ncpu_z;

      npx_ricampionati = intpar[3];
      npx_ricampionati_per_cpu = npx_ricampionati / ncpu_x;
      npy_ricampionati = intpar[4];
      npy_ricampionati_per_cpu = intpar[5];
      npz_ricampionati = intpar[6];
      npz_ricampionati_per_cpu = intpar[7];
      fattore_ricampionamento = intpar[8];
      npx = npx_ricampionati * fattore_ricampionamento;
      npy = npy_ricampionati * fattore_ricampionamento;
      if (npz_ricampionati > 1) npz = npz_ricampionati * fattore_ricampionamento;
      else npz = npz_ricampionati;
      npx_per_cpu = npx / ncpu_x;
      npy_per_cpu = npy / ncpu_y;
      npz_per_cpu = npz / ncpu_z;
    }
    else {
      nptot = (long long int) intpar[16];
      ndv = intpar[17];
    }
  }
  else if (file_version == 4) {
    tnow = realpar[0];
    xmin = realpar[1];
    xmax = realpar[2];
    ymin = realpar[3];
    ymax = realpar[4];
    zmin = realpar[5];
    zmax = realpar[6];

    header_size_bytes = 0;
    /*i_end*/    endianness = intpar[19];

    if (file_griglia) {
      /*
      real_par(1:20) =(/tnow,xmin,xmax,ymin,ymax,zmin,zmax,w0_x,w0_y,&
      n_over_nc,a0,lam0,E0,ompe,targ_in,targ_end,&
      gam0,nb_over_np,b_charge,vbeam/)

      int_par(1:20) = (/ npe_loc, npe_zloc, npe_xloc, nx1, ny1, nz1, &
      jump, ibx, iby, iform, pid, &
      model_id, dmodel_id, nsp, curr_ndim, mp_per_cell(1), &
      nptot, ndv, file_version, i_end / )
      */

      /*npe_xloc*/ ncpu_x = intpar[2];
      /*npe_loc*/  ncpu_y = intpar[0];
      /*npe_zloc*/ ncpu_z = intpar[1];
      ncpu = ncpu_x * ncpu_y * ncpu_z;
      last_cpu = ncpu_x * ncpu_y * ncpu_z;
      /*nx1*/      npx_per_cpu = intpar[3];
      /*jump*/     fattore_ricampionamento = intpar[6];
      /**/         npx_ricampionati_per_cpu = npx_per_cpu / fattore_ricampionamento;
      /*ny1*/      npy_per_cpu = intpar[4];
      /**/         npy_ricampionati_per_cpu = npy_per_cpu / fattore_ricampionamento;
      /*nz1*/      npz_per_cpu = intpar[5];
      /**/         npz_ricampionati_per_cpu = npz_per_cpu / fattore_ricampionamento;
      /**/         npx = npx_per_cpu * ncpu_x;
      /**/         npy = npy_per_cpu * ncpu_y;
      /**/         npz = npz_per_cpu * ncpu_z;
      /**/         npx_ricampionati = npx_ricampionati_per_cpu * ncpu_x;
      /**/         npy_ricampionati = npy_ricampionati_per_cpu * ncpu_y;
      /**/         npz_ricampionati = npz_ricampionati_per_cpu * ncpu_z;
    }
    else {
      /*
      int_par(1:20) = (/ npe, nx, ny_loc, nz_loc, jmp, iby, iform, &
        model_id, dmodel_id, nsp, curr_ndim, mp_per_cell(1), &
        LPf_ord, der_ord, iform, pid, nptot, ndv, file_version, i_end / )
      */
      ncpu = intpar[0];
      last_cpu = intpar[0];
      nptot = (long long int) intpar[16];
      ndv = intpar[17];
    }
  }


#ifdef ENABLE_DEBUG
  debug_read_parameters();
#endif


  if (file_spaziofasi) {
    if (file_version < 3)
    {
      if (ndv == 4 || ndv == 6) p[WEIGHT] = 0;
      else if (ndv == 5 || ndv == 7) p[WEIGHT] = 1;
      else printf("Attention: illegal value for ndv\n"), exit(-17);
      if (ndv == 4 || ndv == 5) zmin = 0.0, zmax = 1.0;
      p[NCOLONNE] = ndv;
      p_b[NCOLONNE] = false;
      p_b[WEIGHT] = false;
    }
    else
    {
      p[WEIGHT] = 1;
      p_b[WEIGHT] = false;
      if (ndv < 7) zmin = 0.0, zmax = 1.0; // a 2D file has 6 floats (columns): x, y, px, py, w, ch
      p[NCOLONNE] = ndv;
      p_b[NCOLONNE] = false;
      if (nptot == -1)
      {
        std::getline(file_dat, riga_persa); // per pulire i caratteri rimanenti sull'ultima riga dei real
        std::getline(file_dat, riga_persa); // per leggere la riga Number of particles
        file_dat >> nptot;
      }
    }
  }
  else {
    if (npz == 1) zmin = 0.0, zmax = 1.0;
    p[WEIGHT] = 0;
    p[NCOLONNE] = (int)npz;
    p_b[NCOLONNE] = false;
    p_b[WEIGHT] = false;

    if (file_version > 2) {
      std::getline(file_dat, riga_persa); // per pulire i caratteri rimanenti sull'ultima riga dei float
      std::getline(file_dat, riga_persa); // per togliere la riga vuota che separa la griglia dai parametri


      for (unsigned int i = 0; i < npx_ricampionati; i++)
      {
        file_dat >> coord;
        xcoord.push_back(coord);
      }
      for (unsigned int i = 0; i < npy_ricampionati; i++)
      {
        file_dat >> coord;
        ycoord.push_back(coord);
      }
      for (unsigned int i = 0; i < npz_ricampionati; i++)
      {
        file_dat >> coord;
        zcoord.push_back(coord);
      }
    }
    else {     // mettiamo una griglia temporanea fissa, che al limite sara' sovrascritta da quella stretchata se presente nel binario
      float dx, dy, dz;
      if (npx_ricampionati > 1) dx = (xmax - xmin) / (npx_ricampionati - 1);
      else dx = (xmax - xmin);
      if (npy_ricampionati > 1) dy = (ymax - ymin) / (npy_ricampionati - 1);
      else dy = (ymax - ymin);
      if (npz_ricampionati > 1) dz = (zmax - zmin) / (npz_ricampionati - 1);
      else dz = (zmax - zmin);

      for (unsigned int i = 0; i < npx_ricampionati; i++)
      {
        coord = xmin + dx*i;
        xcoord.push_back(coord);
      }
      for (unsigned int i = 0; i < npy_ricampionati; i++)
      {
        coord = ymin + dy*i;
        ycoord.push_back(coord);
      }
      for (unsigned int i = 0; i < npz_ricampionati; i++)
      {
        coord = zmin + dz*i;
        zcoord.push_back(coord);
      }
    }
  }
  endian_file = (endianness - 1);
  is_2d_sim = ((ndv == 4 || ndv == 5) && file_version < 3) || (ndv == 6 && file_version >= 3);
}




void Parametri::debug_read_parameters()
{
  std::cout << "Integer parameters" << std::endl;
  for (int i = 0; i < NUMERO_PARAMETRI_FILE_DAT; i++)
  {
    std::cout << std::setw(14) << intpar[i];
    if (i > 0 && !((i + 1) % 4)) std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Real parameters" << std::endl;
  for (int i = 0; i < NUMERO_PARAMETRI_FILE_DAT; i++)
  {
    std::cout << std::setw(14) << realpar[i];
    if (i > 0 && !((i + 1) % 4)) std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "ncpu_x = " << ncpu_x << std::endl;
  std::cout << "ncpu_y = " << ncpu_y << std::endl;
  std::cout << "ncpu_z = " << ncpu_z << std::endl;
  std::cout << "ncpu = " << ncpu << std::endl;
  std::cout << "npx = " << npx << std::endl;
  std::cout << "npy = " << npy << std::endl;
  std::cout << "npz = " << npz << std::endl;
  std::cout << "npx_resampled = " << npx_ricampionati << std::endl;
  std::cout << "npy_resampled = " << npy_ricampionati << std::endl;
  std::cout << "npz_resampled = " << npz_ricampionati << std::endl;
  std::cout << "resampling_factor = " << fattore_ricampionamento << std::endl;
  std::cout << "npx_per_cpu = " << npx_per_cpu << std::endl;
  std::cout << "npy_per_cpu = " << npy_per_cpu << std::endl;
  std::cout << "npz_per_cpu = " << npz_per_cpu << std::endl;
  std::cout << "npx_resampled_per_cpu = " << npx_ricampionati_per_cpu << std::endl;
  std::cout << "npy_resampled_per_cpu = " << npy_ricampionati_per_cpu << std::endl;
  std::cout << "npz_resampled_per_cpu = " << npz_ricampionati_per_cpu << std::endl;
  std::cout << "nptot = " << nptot << std::endl;
  std::cout << "ndv = " << ndv << std::endl;
  std::cout << "endianness = " << endianness << std::endl;
}

void Parametri::chiedi_numero_colonne()
{
  int ncolonne;
  std::cout << "Which file version is this? (1|2|3|4): ";
  std::cin >> file_version;
  if (file_version < 3)
  {
    std::cout << "How many columns are present in the binary file? (4|5|6|7): ";
    std::cin >> ncolonne;
    if (ncolonne == 6 || ncolonne == 4) p[WEIGHT] = 0;
    else if (ncolonne == 7 || ncolonne == 5) p[WEIGHT] = 1;
    else exit(-5);
    p[NCOLONNE] = ncolonne;
    p_b[NCOLONNE] = false;
    p_b[WEIGHT] = false;
  }
  else
  {
    std::cout << "Il file e` di una sim 2D o 3D (scrivi solo il numero)? ";
    std::cin >> ncolonne;
    if (ncolonne == 2) p[NCOLONNE] = 6;
    else if (ncolonne == 3) p[NCOLONNE] = 8;
    else exit(-5);
    p_b[NCOLONNE] = false;
    p[WEIGHT] = 1;
    p_b[WEIGHT] = false;
  }

}


void Parametri::chiedi_2Do3D()
{
  int dimensioni;
  std::cout << "Is it a 3D (3) or 2D (2) grid? ";
  std::cin >> dimensioni;
  if (dimensioni == 2) p[NCOLONNE] = 1, is_2d_sim = true;
  else if (dimensioni == 3) p[NCOLONNE] = 3;
  else
  {
    std::cout << "Invalid choice" << std::endl;
    exit(-5);
  }
  p_b[NCOLONNE] = false;
}


void Parametri::chiedi_endian_file()
{
  std::cout << "Tell me something about endianness: is it little [x86] (0) or big [ppc] (1)? ";
  std::cin >> endian_file;
  if (endian_file != 1 && endian_file != 0) exit(-4);
}


void Parametri::check_filename(const char *nomefile)
{
  if (nomefile[0] == 'P')
  {
    if (nomefile[1] == 'r')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)MP_MEV;
        file_particelle_P = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_protoni = true;
        file_griglia = true;
        sprintf(support_label, "pren");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'd')
    {
      file_densita_protoni = true;
      file_griglia = true;
      sprintf(support_label, "pden");
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else if (nomefile[0] == 'H')
  {
    if (nomefile[1] == 'i')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)MP_MEV; // fix wrong!
        file_particelle_HI = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'd')
      {
        file_densita_HI = true;
        file_griglia = true;
        sprintf(support_label, "hidn");
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_HI = true;
        file_griglia = true;
        sprintf(support_label, "hien");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == '1')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)MP_MEV; // fix wrong!
        file_particelle_generic_ion = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'd')
      {
        file_densita_generic_ion = true;
        file_griglia = true;
        sprintf(support_label, "h1dn");
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_generic_ion = true;
        file_griglia = true;
        sprintf(support_label, "h1en");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == '2')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)MP_MEV; // fix wrong!
        file_particelle_generic_ion = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'd')
      {
        file_densita_generic_ion = true;
        file_griglia = true;
        sprintf(support_label, "h2dn");
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_generic_ion = true;
        file_griglia = true;
        sprintf(support_label, "h2en");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else if (nomefile[0] == 'L')
  {
    if (nomefile[1] == 'i')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)MP_MEV; // fix wrong!
        file_particelle_LI = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'd')
      {
        file_densita_LI = true;
        file_griglia = true;
        sprintf(support_label, "lidn");
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_LI = true;
        file_griglia = true;
        sprintf(support_label, "lien");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else if (nomefile[0] == 'E')
  {
    if (nomefile[1] == 'l')
    {
      if (nomefile[2] == 'p')
      {
        massa_particella_MeV = (float)ME_MEV;
        file_particelle_E = true;
        file_spaziofasi = true;
      }
      else if (nomefile[2] == 'e')
      {
        file_densita_energia_griglia_elettroni = true;
        file_griglia = true;
        sprintf(support_label, "elen");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'x')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_Ex = true;
        file_griglia = true;
        sprintf(support_label, "Ex");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'y')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_Ey = true;
        file_griglia = true;
        sprintf(support_label, "Ey");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'z')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_Ez = true;
        file_griglia = true;
        sprintf(support_label, "Ez");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'd')
    {
      file_densita_elettroni = true;
      file_griglia = true;
      sprintf(support_label, "eden");
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else if (nomefile[0] == 'B')
  {
    if (nomefile[1] == 'x')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_Bx = true;
        file_griglia = true;
        sprintf(support_label, "Bx");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'y')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_By = true;
        file_griglia = true;
        sprintf(support_label, "By");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'z')
    {
      if (nomefile[2] == 'f')
      {
        file_campi_Bz = true;
        file_griglia = true;
        sprintf(support_label, "Bz");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'd')
    {
      file_densita_driver = true;
      file_griglia = true;
      sprintf(support_label, "Bd");
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else if (nomefile[0] == 'J')
  {
    if (nomefile[1] == 'x')
    {
      if (nomefile[2] == 'f')
      {
        file_correnti_Jx = true;
        file_griglia = true;
        sprintf(support_label, "Jx");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'y')
    {
      if (nomefile[2] == 'f')
      {
        file_correnti_Jy = true;
        file_griglia = true;
        sprintf(support_label, "Jy");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else if (nomefile[1] == 'z')
    {
      if (nomefile[2] == 'f')
      {
        file_correnti_Jz = true;
        file_griglia = true;
        sprintf(support_label, "Jz");
      }
      else
      {
        std::cout << "Unrecognized file" << std::endl;
        exit(-15);
      }
    }
    else
    {
      std::cout << "Unrecognized file" << std::endl;
      exit(-15);
    }
  }
  else
  {
    std::cout << "Unrecognized file" << std::endl;
    exit(-15);
  }
}


void Parametri::check_forced_version(const int cl_argc, const char ** cl_argv)
{
  argc = cl_argc;
  argv = new std::string[argc];
  for (int i = 0; i < argc; i++) argv[i] = std::string(cl_argv[i]);

  for (int i = 2; i < argc; i++) {
    if (argv[i] == "-force_v1") {
      std::cout << "Forced using routines for file v1" << std::endl;
      file_version = 1;
      fixed_aladyn_version = true;
    }
    else if (argv[i] == "-force_v2") {
      std::cout << "Forced using routines for file v2" << std::endl;
      file_version = 2;
      fixed_aladyn_version = true;
    }
    else if (argv[i] == "-force_v3") {
      std::cout << "Forced using routines for file v3" << std::endl;
      file_version = 3;
      fixed_aladyn_version = true;
    }
    else if (argv[i] == "-force_v4") {
      std::cout << "Forced using routines for file v4" << std::endl;
      file_version = 4;
      fixed_aladyn_version = true;
    }
  }
}




void Parametri::parse_command_line()
{
  std::ifstream fileParametri;
  std::string nomefile;
  bool usa_file_parametri = false;
  bool failed_opening_file;

  for (int i = 2; i < argc; i++)
    /************************************************************************
    We will iterate over argv[] to get the parameters stored inside.
    Note that we're starting on 1 because we don't need to know the
    path of the program, which is stored in argv[0], and the input file,
    which is supposed to be given as the first argument and so is in argv[1]
    ************************************************************************/
  {
    if (argv[i] == "-readParamsfromFile" || argv[i] == "-readParamsFromFile" || argv[i] == "-readParams" || argv[i] == "-readparamsfromfile")
    {
      if (i < argc - 1 && argv[i + 1][0] != '-')
      {
        nomefile = std::string(argv[i + 1]);
        usa_file_parametri = true;
        i++;
        std::cout << "Using " << nomefile << " as the binning parameters file" << std::endl;
      }
      else
      {
        nomefile = filebasename + ".extremes";
        usa_file_parametri = true;
        std::cout << "Using " << nomefile << " as the binning parameters file" << std::endl;
      }
    }
    else if (argv[i] == "-params")
    {
      std::cout << "Enabled the output of the parameters from .dat/.bin files" << std::endl;
      p[OUT_PARAMS] = 1;
      p_b[OUT_PARAMS] = false;
    }
    else if (argv[i] == "-swap")
    {
      std::cout << "Forcing byte swapping (endianness)" << std::endl;
      p[SWAP] = 1;
      p_b[SWAP] = false;
    }
    else if (argv[i] == "-noswap")
    {
      std::cout << "Forcing byte NON swapping (endianness)" << std::endl;
      p[SWAP] = 0;
      p_b[SWAP] = false;
    }
    else if (argv[i] == "-stop")
    {
      last_cpu = atoi(argv[i + 1].c_str());
      if (last_cpu < 1) last_cpu = 1;
      std::cout << "Forced stopping reading at CPU #" << last_cpu << std::endl;
      i++;
    }
    else if (argv[i] == "-span")
    {
      span = atoi(argv[i + 1].c_str());
      if (span < 0) span = 0;
      std::cout << "Span factor for lineout: " << span << std::endl;
      i++;
    }
    else if (argv[i] == "-subsample")
    {
      subsample = atoi(argv[i + 1].c_str());
      if (file_particelle_P || file_particelle_E || file_particelle_HI || file_particelle_LI)
      {
        if (subsample < 1)
        {
          subsample = 1;
          std::cout << "Value for subsampling not valid, disabled" << std::endl;
        }
        else
        {
          std::cout << "Will subsample with a ratio of 1:" << subsample << " if any ASCII dump will be requested" << std::endl;
        }
      }
      else
      {
        std::cout << "Subsample factor is valid only for phase space files and will be used only for ASCII output" << std::endl;
      }
      i++;
    }
    else if (argv[i] == "-ncol")
    {
      int ncolumns = atoi(argv[i + 1].c_str());
      p[NCOLONNE] = ncolumns;
      if (ncolumns == 6) p[WEIGHT] = 0;
      else if (ncolumns == 7) p[WEIGHT] = 1;
      std::cout << "Forced number of columns in binary file to " << ncolumns << std::endl;
      p_b[NCOLONNE] = false;
      p_b[WEIGHT] = false;
      i++;
    }
    else if (argv[i] == "-dump_vtk")
    {
      std::cout << "You asked to have a VTK dump of the input file" << std::endl;
      p[OUT_VTK] = 1;
      p_b[OUT_VTK] = false;
    }
    else if (argv[i] == "-dump_vtk_nostretch")
    {
      std::cout << "You asked to have a VTK dump of the non-stretched grid.\n";
      std::cout << "If not explicitly said, the grid will be considered stretched in ALL directions" << std::endl;
      p[OUT_VTK_NOSTRETCH] = 1;
      p_b[OUT_VTK_NOSTRETCH] = false;
    }
    else if (argv[i] == "-no_stretch_x")
    {
      std::cout << "Assuming the grid is NOT stretched along x axis.\n";
      stretched_along_x = 0;
    }
    else if (argv[i] == "-dump_cutx")
    {
      if (p[NCOLONNE] > 1)
      {
        if (argv[i + 1][0] != '-')
        {
          float posizione_taglio = (float)atof(argv[i + 1].c_str());
          posizioni_taglio_griglia_x.push_back(posizione_taglio);
          std::cout << "You asked to cut the grid at x = " << posizione_taglio << std::endl;
          i++;
        }
        else
        {
          std::cout << "You asked to cut the grid at the middle of the x-axis" << std::endl;
        }
        p[OUT_CUTX] = 1;
        p_b[OUT_CUTX] = false;
      }
      else
      {
        std::cout << "Unable to apply a cut on the grid in 2D, please use -dump_gnuplot" << std::endl;
        if (argv[i + 1][0] != '-') i++;
        p[OUT_CUTX] = 0;
        p_b[OUT_CUTX] = false;
      }
    }

    else if (argv[i] == "-dump_cuty")
    {
      if (p[NCOLONNE] > 1)
      {
        if (argv[i + 1][0] != '-')
        {
          float posizione_taglio = (float)atof(argv[i + 1].c_str());
          posizioni_taglio_griglia_y.push_back(posizione_taglio);
          std::cout << "You asked to cut the grid at y = " << posizione_taglio << std::endl;
          i++;
        }
        else
        {
          std::cout << "You asked to cut the grid at the middle of the y-axis" << std::endl;
        }
        p[OUT_CUTY] = 1;
        p_b[OUT_CUTY] = false;
      }
      else
      {
        std::cout << "Unable to apply a cut on the grid in 2D, please use -dump_gnuplot" << std::endl;
        if (argv[i + 1][0] != '-') i++;
        p[OUT_CUTY] = 0;
        p_b[OUT_CUTY] = false;
      }
    }

    else if (argv[i] == "-dump_cutz")
    {
      if (p[NCOLONNE] > 1)
      {
        if (argv[i + 1][0] != '-')
        {
          float posizione_taglio = (float)atof(argv[i + 1].c_str());
          posizioni_taglio_griglia_z.push_back(posizione_taglio);
          std::cout << "You asked to cut the grid at z = " << posizione_taglio << std::endl;
          i++;
        }
        else
        {
          std::cout << "You asked to cut the grid at the middle of the z-axis" << std::endl;
        }
        p[OUT_CUTZ] = 1;
        p_b[OUT_CUTZ] = false;
      }
      else
      {
        std::cout << "Unable to apply a cut on the grid in 2D, please use -dump_gnuplot" << std::endl;
        if (argv[i + 1][0] != '-') i++;
        p[OUT_CUTZ] = 0;
        p_b[OUT_CUTZ] = false;
      }
    }

    else if (argv[i] == "-dump_lineoutx")
    {
      std::cout << "You asked to have a lineout of the grid along the x-axis" << std::endl;
      p[OUT_LINEOUT_X] = 1;
      p_b[OUT_LINEOUT_X] = false;
    }

    else if (argv[i] == "-dump_gnuplot")
    {
      if (p[NCOLONNE] == 1)
      {
        std::cout << "You asked to rewrite the 2D grid in ASCII format for gnuplot" << std::endl;
        p[OUT_GRID2D] = 1;
        p_b[OUT_GRID2D] = false;
      }
      else
      {
        std::cout << "Unable to write a 3D grid for gnuplot without slicing it, please use dump_cutx/y/z" << std::endl;
        p[OUT_GRID2D] = 0;
        p_b[OUT_GRID2D] = false;
      }
    }
    else if (argv[i] == "-dump_propaga")
    {
      std::cout << "You asked to have a .ppg dump of the input phase space" << std::endl;
      p[OUT_PROPAGA] = 1;
      p_b[OUT_PROPAGA] = false;
    }
    else if (argv[i] == "-dump_csv")
    {
      std::cout << "You asked to have a .csv dump of the input phase space" << std::endl;
      p[OUT_CSV] = 1;
      p_b[OUT_CSV] = false;
    }
    else if (argv[i] == "-dump_xyzE")
    {
      std::cout << "You asked to have a xy(z)E dump of the input phase space" << std::endl;
      p[OUT_XYZE] = 1;
      p_b[OUT_XYZE] = false;
    }
    else if (argv[i] == "-dump_clean")
    {
      std::cout << "You asked to have a unique, clean binary file as the output" << std::endl;
      p[OUT_CLEAN_BINARY] = 1;
      p_b[OUT_CLEAN_BINARY] = false;
    }
    else if (argv[i] == "-parameters")
    {
      std::cout << "You asked to write the simulation parameters file" << std::endl;
      p[OUT_PARAMS] = 1;
      p_b[OUT_PARAMS] = false;
    }
    else if (argv[i] == "-find_minmax")
    {
      std::cout << "You asked to search for minima and maxima" << std::endl;
      p[FIND_MINMAX] = 1;
      p_b[FIND_MINMAX] = false;
    }
    else if (argv[i] == "-do_binning")
    {
      std::cout << "You asked to enable plotting functions" << std::endl;
      p[DO_BINNING] = 1;
      p_b[DO_BINNING] = false;
    }
    else if (argv[i] == "-xmin")
    {
      xmin = (float)atof(argv[i + 1].c_str());
      xmin_b = false;
      i++;
    }
    else if (argv[i] == "-xmax")
    {
      xmax = (float)atof(argv[i + 1].c_str());
      xmax_b = false;
      i++;
    }
    else if (argv[i] == "-weight")
    {
      overwrite_weight = true;
      overwrite_weight_value = (float)atof(argv[i + 1].c_str());
      i++;
    }
    else if (argv[i] == "-charge")
    {
      overwrite_charge = true;
      overwrite_charge_value = (float)atof(argv[i + 1].c_str());
      i++;
    }
    else if (argv[i] == "-wmin")
    {
      wmin = (float)atof(argv[i + 1].c_str());
      wmin_b = false;
      i++;
    }
    else if (argv[i] == "-wmax")
    {
      wmax = (float)atof(argv[i + 1].c_str());
      wmax_b = false;
      i++;
    }
    else if (argv[i] == "-chmin")
    {
      chmin = (float)atof(argv[i + 1].c_str());
      chmin_b = false;
      i++;
    }
    else if (argv[i] == "-chmax")
    {
      chmax = (float)atof(argv[i + 1].c_str());
      chmax_b = false;
      i++;
    }
    else if (argv[i] == "-ymin")
    {
      ymin = (float)atof(argv[i + 1].c_str());
      ymin_b = false;
      i++;
    }
    else if (argv[i] == "-ymax")
    {
      ymax = (float)atof(argv[i + 1].c_str());
      ymax_b = false;
      i++;
    }
    else if (argv[i] == "-zmin")
    {
      if (p[NCOLONNE] > 5)
      {
        zmin = (float)atof(argv[i + 1].c_str());
        zmin_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-zmax")
    {
      if (p[NCOLONNE] > 5)
      {
        zmax = (float)atof(argv[i + 1].c_str());
        zmax_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-tymin")
    {
      tymin = (float)atof(argv[i + 1].c_str());
      tymin_b = false;
      i++;
    }
    else if (argv[i] == "-tymax")
    {
      tymax = (float)atof(argv[i + 1].c_str());
      tymax_b = false;
      i++;
    }
    else if (argv[i] == "-tzmin")
    {
      if (p[NCOLONNE] > 5)
      {
        tzmin = (float)atof(argv[i + 1].c_str());
        tzmin_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-tzmax")
    {
      if (p[NCOLONNE] > 5)
      {
        tzmax = (float)atof(argv[i + 1].c_str());
        tzmax_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-pxmin")
    {
      pxmin = (float)atof(argv[i + 1].c_str());
      pxmin_b = false;
      i++;
    }
    else if (argv[i] == "-pxmax")
    {
      pxmax = (float)atof(argv[i + 1].c_str());
      pxmax_b = false;
      i++;
    }
    else if (argv[i] == "-pymin")
    {
      pymin = (float)atof(argv[i + 1].c_str());
      pymin_b = false;
      i++;
    }
    else if (argv[i] == "-pymax")
    {
      pymax = (float)atof(argv[i + 1].c_str());
      pymax_b = false;
      i++;
    }
    else if (argv[i] == "-pzmin")
    {
      if (p[NCOLONNE] > 5)
      {
        pzmin = (float)atof(argv[i + 1].c_str());
        pzmin_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-pzmax")
    {
      if (p[NCOLONNE] > 5)
      {
        pzmax = (float)atof(argv[i + 1].c_str());
        pzmax_b = false;
        i++;
      }
      else
      {
        std::cout << "Unable to apply a cut in z-dimension on a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-thetamin")
    {
      thetamin = (float)atof(argv[i + 1].c_str());
      thetamin_b = false;
      i++;
    }
    else if (argv[i] == "-thetamax")
    {
      thetamax = (float)atof(argv[i + 1].c_str());
      thetamax_b = false;
      i++;
    }
    else if (argv[i] == "-thetaTmin")
    {
      thetaTmin = (float)atof(argv[i + 1].c_str());
      thetaTmin_b = false;
      i++;
    }
    else if (argv[i] == "-thetaTmax")
    {
      thetaTmax = (float)atof(argv[i + 1].c_str());
      thetaTmax_b = false;
      i++;
    }
    else if (argv[i] == "-gammamin")
    {
      gammamin = (float)atof(argv[i + 1].c_str());
      gammamin_b = false;
      i++;
    }
    else if (argv[i] == "-gammamax")
    {
      gammamax = (float)atof(argv[i + 1].c_str());
      gammamax_b = false;
      i++;
    }
    else if (argv[i] == "-Emin")
    {
      Emin = (float)atof(argv[i + 1].c_str());
      Emin_b = false;
      i++;
    }
    else if (argv[i] == "-Emax")
    {
      Emax = (float)atof(argv[i + 1].c_str());
      Emax_b = false;
      i++;
    }
    else if (argv[i] == "-plot_xy")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_xy = 1;
    }
    else if (argv[i] == "-plot_xw")
    {
      if (p[WEIGHT])
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_xw = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with weight using a file without weight!" << std::endl;
      }
    }
    else if (argv[i] == "-plot_xz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_xz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_yz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_yz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_rcf")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_rcf = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with tz using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_xpx")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_xpx = 1;
    }
    else if (argv[i] == "-plot_xpy")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_xpy = 1;
    }
    else if (argv[i] == "-plot_xpz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_xpz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_ypx")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_ypx = 1;
    }
    else if (argv[i] == "-plot_ypy")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_ypy = 1;
    }
    else if (argv[i] == "-plot_ypz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_ypz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_zpx")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_zpx = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_zpy")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_zpy = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_zpz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_zpz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_pxpy")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_pxpy = 1;
    }
    else if (argv[i] == "-plot_pxpz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_pxpz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_pypz")
    {
      if (p[NCOLONNE] > 5)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_pypz = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with z using a 2D file" << std::endl;
      }
    }
    else if (argv[i] == "-plot_etheta")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_Etheta = 1;
    }
    else if (argv[i] == "-plot_ethetaT")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_EthetaT = 1;
    }
    else if (argv[i] == "-plot_espec")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_Espec = 1;
    }
    else if (argv[i] == "-plot_chspec")
    {
      if (file_version >= 3)
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_chspec = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with charge using a file without charges!" << std::endl;
      }
    }
    else if (argv[i] == "-plot_wspec")
    {
      if (p[WEIGHT])
      {
        if (p_b[DO_BINNING]) {
          std::cout << "You asked to enable plotting functions" << std::endl;
          p[DO_BINNING] = 1;
          p_b[DO_BINNING] = false;
        }
        fai_plot_wspec = 1;
      }
      else
      {
        std::cout << "Unable to do a plot with weight using a file without weights!" << std::endl;
      }
    }
    else if (argv[i] == "-plot_thetaspec")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_thetaspec = 1;
    }
    else if (argv[i] == "-plot_thetaTspec")
    {
      if (p_b[DO_BINNING]) {
        std::cout << "You asked to enable plotting functions" << std::endl;
        p[DO_BINNING] = 1;
        p_b[DO_BINNING] = false;
      }
      fai_plot_thetaTspec = 1;
    }
    else if (argv[i] == "-nbin")
    {
      nbin = atoi(argv[i + 1].c_str());
      if (nbin_x_b) nbin_x = nbin;
      if (nbin_y_b) nbin_y = nbin;
      if (nbin_z_b) nbin_z = nbin;
      if (nbin_px_b) nbin_px = nbin;
      if (nbin_py_b) nbin_py = nbin;
      if (nbin_pz_b) nbin_pz = nbin;
      if (nbin_ty_b) nbin_ty = nbin;
      if (nbin_tz_b) nbin_tz = nbin;
      if (nbin_gamma_b) nbin_gamma = nbin;
      if (nbin_theta_b) nbin_theta = nbin;
      if (nbin_theta_b) nbin_thetaT = nbin;
      if (nbin_E_b) nbin_E = nbin;
      if (nbin_w_b) nbin_w = nbin;
      if (nbin_ch_b) nbin_ch = nbin;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinx")
    {
      nbin_x = atoi(argv[i + 1].c_str());
      nbin_x_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbiny")
    {
      nbin_y = atoi(argv[i + 1].c_str());
      nbin_y_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinz")
    {
      nbin_z = atoi(argv[i + 1].c_str());
      nbin_z_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinty")
    {
      nbin_ty = atoi(argv[i + 1].c_str());
      nbin_ty_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbintz")
    {
      nbin_tz = atoi(argv[i + 1].c_str());
      nbin_tz_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinpx")
    {
      nbin_px = atoi(argv[i + 1].c_str());
      nbin_px_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinpy")
    {
      nbin_py = atoi(argv[i + 1].c_str());
      nbin_py_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinpz")
    {
      nbin_pz = atoi(argv[i + 1].c_str());
      nbin_pz_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbintheta")
    {
      nbin_theta = atoi(argv[i + 1].c_str());
      nbin_theta_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinthetaT")
    {
      nbin_thetaT = atoi(argv[i + 1].c_str());
      nbin_thetaT_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbingamma")
    {
      nbin_gamma = atoi(argv[i + 1].c_str());
      nbin_gamma_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinE")
    {
      nbin_E = atoi(argv[i + 1].c_str());
      nbin_E_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinw")
    {
      nbin_w = atoi(argv[i + 1].c_str());
      nbin_w_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-nbinch")
    {
      nbin_ch = atoi(argv[i + 1].c_str());
      nbin_ch_b = false;
      nbin_b = false;
      i++;
    }
    else if (argv[i] == "-dontask")
    {
      do_not_ask_missing = true;
    }
  }


  std::string nomepar, evita, leggi;

  if (file_particelle_P || file_particelle_E || file_particelle_HI || file_particelle_LI || file_particelle_generic_ion)
  {
    if (usa_file_parametri)
    {
      fileParametri.open(nomefile.c_str());
      failed_opening_file = fileParametri.fail();
      if (failed_opening_file)
      {
        std::cout << "Unable to open file " << nomefile << " which contains the binning parameters" << std::endl;
        exit(50);
      }
      while (!fileParametri.eof())
      {
        fileParametri >> nomepar >> evita >> leggi;
        if ((nomepar == "xmin" || nomepar == "XMIN") && xmin_b)
        {
          xmin = (float)std::atof(leggi.c_str());
          xmin_b = false;
        }
        else if ((nomepar == "xmax" || nomepar == "XMAX") && xmax_b)
        {
          xmax = (float)std::atof(leggi.c_str());
          xmax_b = false;
        }
        else if ((nomepar == "ymin" || nomepar == "YMIN") && ymin_b)
        {
          ymin = (float)std::atof(leggi.c_str());
          ymin_b = false;
        }
        else if ((nomepar == "ymax" || nomepar == "YMAX") && ymax_b)
        {
          ymax = (float)std::atof(leggi.c_str());
          ymax_b = false;
        }
        else if ((nomepar == "zmin" || nomepar == "ZMIN") && zmin_b)
        {
          zmin = (float)std::atof(leggi.c_str());
          zmin_b = false;
        }
        else if ((nomepar == "zmax" || nomepar == "ZMAX") && zmax_b)
        {
          zmax = (float)std::atof(leggi.c_str());
          zmax_b = false;
        }
        else if ((nomepar == "tymin" || nomepar == "TYMIN") && tymin_b)
        {
          tymin = (float)std::atof(leggi.c_str());
          tymin_b = false;
        }
        else if ((nomepar == "tymax" || nomepar == "TYMAX") && tymax_b)
        {
          tymax = (float)std::atof(leggi.c_str());
          tymax_b = false;
        }
        else if ((nomepar == "tzmin" || nomepar == "TZMIN") && tzmin_b)
        {
          tzmin = (float)std::atof(leggi.c_str());
          tzmin_b = false;
        }
        else if ((nomepar == "tzmax" || nomepar == "TZMAX") && tzmax_b)
        {
          tzmax = (float)std::atof(leggi.c_str());
          tzmax_b = false;
        }
        else if ((nomepar == "pxmin" || nomepar == "PXMIN") && pxmin_b)
        {
          pxmin = (float)std::atof(leggi.c_str());
          pxmin_b = false;
        }
        else if ((nomepar == "pxmax" || nomepar == "PXMAX") && pxmax_b)
        {
          pxmax = (float)std::atof(leggi.c_str());
          pxmax_b = false;
        }
        else if ((nomepar == "pymin" || nomepar == "PYMIN") && pymin_b)
        {
          pymin = (float)std::atof(leggi.c_str());
          pymin_b = false;
        }
        else if ((nomepar == "pymax" || nomepar == "PYMAX") && pymax_b)
        {
          pymax = (float)std::atof(leggi.c_str());
          pymax_b = false;
        }
        else if ((nomepar == "pzmin" || nomepar == "PZMIN") && pzmin_b)
        {
          pzmin = (float)std::atof(leggi.c_str());
          pzmin_b = false;
        }
        else if ((nomepar == "pzmax" || nomepar == "PZMAX") && pzmax_b)
        {
          pzmax = (float)std::atof(leggi.c_str());
          pzmax_b = false;
        }
        else if ((nomepar == "gammamin" || nomepar == "GAMMAMIN") && gammamin_b)
        {
          gammamin = (float)std::atof(leggi.c_str());
          gammamin_b = false;
        }
        else if ((nomepar == "gammamax" || nomepar == "GAMMAMAX") && gammamax_b)
        {
          gammamax = (float)std::atof(leggi.c_str());
          gammamax_b = false;
        }
        else if ((nomepar == "thetamin" || nomepar == "THETAMIN") && thetamin_b)
        {
          thetamin = (float)std::atof(leggi.c_str());
          thetamin_b = false;
        }
        else if ((nomepar == "thetamax" || nomepar == "THETAMAX") && thetamax_b)
        {
          thetamax = (float)std::atof(leggi.c_str());
          thetamax_b = false;
        }
        else if ((nomepar == "thetaradmin" || nomepar == "THETARADMIN") && thetaTmin_b)
        {
          thetaTmin = (float)std::atof(leggi.c_str());
          thetaTmin_b = false;
        }
        else if ((nomepar == "thetaradmax" || nomepar == "THETARADMAX") && thetaTmax_b)
        {
          thetaTmax = (float)std::atof(leggi.c_str());
          thetaTmax_b = false;
        }
        else if ((nomepar == "emin" || nomepar == "EMIN") && Emin_b)
        {
          Emin = (float)std::atof(leggi.c_str());
          Emin_b = false;
        }
        else if ((nomepar == "emax" || nomepar == "EMAX") && Emax_b)
        {
          Emax = (float)std::atof(leggi.c_str());
          Emax_b = false;
        }
        else if ((nomepar == "wmin" || nomepar == "WMIN") && wmin_b)
        {
          wmin = (float)std::atof(leggi.c_str());
          wmin_b = false;
        }
        else if ((nomepar == "wmax" || nomepar == "WMAX") && wmax_b)
        {
          wmax = (float)std::atof(leggi.c_str());
          wmax_b = false;
        }
        else if ((nomepar == "chmin" || nomepar == "CHMIN") && chmin_b)
        {
          chmin = (float)std::atof(leggi.c_str());
          chmin_b = false;
        }
        else if ((nomepar == "chmax" || nomepar == "CHMAX") && chmax_b)
        {
          chmax = (float)std::atof(leggi.c_str());
          chmax_b = false;
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
      std::cout << "Do you want to find minimum and maximum values for common parameters? 0 (NO) - 1 (YES): ";
      std::cin >> p[FIND_MINMAX];
      p_b[FIND_MINMAX] = false;
    }
    if (p_b[DO_BINNING] && !do_not_ask_missing)
    {
      std::cout << "Do you want to do a histogram (data binning)? 0 (NO) - 1 (YES): ";
      std::cin >> p[DO_BINNING];
      p_b[DO_BINNING] = false;
    }
    if (p[DO_BINNING] == 1 && nbin_b && !do_not_ask_missing)
    {
      std::cout << "How many bins per axis? (common ALaDyn choice: 120): ";
      std::cin >> nbin;
      nbin_x = nbin_y = nbin_z = nbin_px = nbin_py = nbin_pz = nbin_E = nbin_theta = nbin_thetaT = nbin_ty = nbin_tz = nbin_w = nbin_ch = nbin;
    }

    if (p[DO_BINNING] == 1 && !do_not_ask_missing)
    {
      std::cout << "Do you want to do an x-px plot? 0 (NO) - 1 (YES): ";
      std::cin >> fai_plot_xpx;
      std::cout << "E-theta (deg)? 0 (NO) - 1 (YES): ";
      std::cin >> fai_plot_Etheta;
      std::cout << "E-theta (rad)? 0 (NO) - 1 (YES): ";
      std::cin >> fai_plot_EthetaT;
      std::cout << "Energy spectrum? 0 (NO) - 1 (YES): ";
      std::cin >> fai_plot_Espec;
      std::cout << "RFC plot? 0 (NO) - 1 (YES): ";
      std::cin >> fai_plot_rcf;
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
        if (pxmin_b)
        {
          std::cout << "pxmin = ";
          std::cin >> pxmin;
          pxmin_b = false;
        }
        if (pxmax_b)
        {
          std::cout << "pxmax = ";
          std::cin >> pxmax;
          pxmax_b = false;
        }
        if (nbin_px_b)
        {
          std::cout << "nbin_px = ";
          std::cin >> nbin_px;
          nbin_px_b = false;
        }
      }
      if (fai_plot_Etheta || fai_plot_Espec || fai_plot_EthetaT)
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
      if (fai_plot_EthetaT)
      {
        if (thetaTmin_b)
        {
          std::cout << "thetaRADmin = ";
          std::cin >> thetaTmin;
          thetaTmin_b = false;
        }
        if (thetaTmax_b)
        {
          std::cout << "thetaRADmax = ";
          std::cin >> thetaTmax;
          thetaTmax_b = false;
        }
        if (nbin_thetaT_b)
        {
          std::cout << "nbin_thetaRAD = ";
          std::cin >> nbin_thetaT;
          nbin_thetaT_b = false;
        }
      }
      if (fai_plot_rcf)
      {
        if (tymin_b)
        {
          std::cout << "tymin = ";
          std::cin >> tymin;
          tymin_b = false;
        }
        if (tymax_b)
        {
          std::cout << "tymax = ";
          std::cin >> tymax;
          tymax_b = false;
        }
        if (nbin_ty_b)
        {
          std::cout << "nbin_ty = ";
          std::cin >> nbin_ty;
          nbin_ty_b = false;
        }
        if (tzmin_b)
        {
          std::cout << "tzmin = ";
          std::cin >> tzmin;
          tzmin_b = false;
        }
        if (tzmax_b)
        {
          std::cout << "tzmax = ";
          std::cin >> tzmax;
          tzmax_b = false;
        }
        if (nbin_tz_b)
        {
          std::cout << "nbin_tz = ";
          std::cin >> nbin_tz;
          nbin_tz_b = false;
        }
      }
    }




#ifdef ENABLE_DEBUG
    std::cout << "In file " << nomefile << " I found these binning parameters:" << std::endl;
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
    std::cout << "THETARADMIN = " << thetaTmin << std::endl;
    std::cout << "THETARADMAX = " << thetaTmax << std::endl;
    std::cout << "EMIN = " << Emin << std::endl;
    std::cout << "EMAX = " << Emax << std::endl;
    std::cout << "TYMIN = " << tymin << std::endl;
    std::cout << "TYMAX = " << tymax << std::endl;
    std::cout << "TZMIN = " << tzmin << std::endl;
    std::cout << "TZMAX = " << tzmax << std::endl;
    std::cout << "WMIN = " << wmin << std::endl;
    std::cout << "WMAX = " << wmax << std::endl;
    std::cout << "CHMIN = " << chmin << std::endl;
    std::cout << "CHMAX = " << chmax << std::endl;
#endif
    if (p_b[OUT_VTK] && !do_not_ask_missing)
    {
      std::cout << "Do you want the .vtk binary output?? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_VTK];
      p_b[OUT_VTK] = false;
    }
    if (p_b[OUT_CLEAN_BINARY] && !do_not_ask_missing)
    {
      std::cout << "Do you want the .bin output, cleaned from Fortran metadata? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_CLEAN_BINARY];
      p_b[OUT_CLEAN_BINARY] = false;
    }
    if (p_b[OUT_PROPAGA] && !do_not_ask_missing)
    {
      std::cout << "Do you want the .ppg output for Propaga? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_PROPAGA];
      p_b[OUT_PROPAGA] = false;
    }
    if (p_b[OUT_XYZE] && !do_not_ask_missing)
    {
      std::cout << "Do you want a .txt file with x y (z) and Energy? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_XYZE];
      p_b[OUT_XYZE] = false;
    }
    if (p_b[OUT_CSV] && !do_not_ask_missing)
    {
      std::cout << "Do you want a .csv file for Paraview? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_CSV];
      p_b[OUT_CSV] = false;
    }
    if (p_b[OUT_PARAMS] && !do_not_ask_missing)
    {
      std::cout << "Do you want a .dat files with simulation parameters? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_PARAMS];
      p_b[OUT_PARAMS] = false;
    }
  }
  else
  {
    if (p_b[OUT_VTK] && !do_not_ask_missing)
    {
      std::cout << "Do you want the .vtk binary output?? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_VTK];
      p_b[OUT_VTK] = false;
    }
    if (p_b[OUT_VTK_NOSTRETCH] && !do_not_ask_missing)
    {
      std::cout << "Do you want the .vtk binary output only for the unstretched part of the grid? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_VTK_NOSTRETCH];
      p_b[OUT_VTK_NOSTRETCH] = false;
    }
    if (p[OUT_VTK_NOSTRETCH] && !do_not_ask_missing)
    {
      std::cout << "Is the grid stretched also along x? 0 (NO) - 1 (YES): ";
      std::cin >> stretched_along_x;
    }
    if (p[NCOLONNE] > 1)
    {
      if (p_b[OUT_CUTX] && !do_not_ask_missing)
      {
        std::cout << "Do you want a .txt from a slice along x, for gnuplot? 0 (NO) - 1 (YES): ";
        std::cin >> p[OUT_CUTX];
        p_b[OUT_CUTX] = false;
        float posizione_taglio = 0.0;
        if (p[OUT_CUTX] == 1)
        {
          std::cout << "Please tell me at which position should I cut the slice (in micrometers): ";
          std::cin >> posizione_taglio;
          posizioni_taglio_griglia_x.push_back(posizione_taglio);
        }
      }
      if (p_b[OUT_CUTY] && !do_not_ask_missing)
      {
        std::cout << "Do you want a .txt from a slice along y, for gnuplot? 0 (NO) - 1 (YES): ";
        std::cin >> p[OUT_CUTY];
        p_b[OUT_CUTY] = false;
        float posizione_taglio = 0.0;
        if (p[OUT_CUTY] == 1)
        {
          std::cout << "Please tell me at which position should I cut the slice (in micrometers): ";
          std::cin >> posizione_taglio;
          posizioni_taglio_griglia_y.push_back(posizione_taglio);
        }
      }
      if (p_b[OUT_CUTZ] && !do_not_ask_missing)
      {
        std::cout << "Do you want a .txt from a slice along z, for gnuplot? 0 (NO) - 1 (YES): ";
        std::cin >> p[OUT_CUTZ];
        p_b[OUT_CUTZ] = false;
        float posizione_taglio = 0.0;
        if (p[OUT_CUTZ] == 1)
        {
          std::cout << "Please tell me at which position should I cut the slice (in micrometers): ";
          std::cin >> posizione_taglio;
          posizioni_taglio_griglia_z.push_back(posizione_taglio);
        }
      }
      p[OUT_GRID2D] = 0;
      p_b[OUT_GRID2D] = false;
    }
    else
    {
      if (p_b[OUT_GRID2D] && !do_not_ask_missing)
      {
        std::cout << "Do you want a .txt file for gnuplot? 0 (NO) - 1 (YES): ";
        std::cin >> p[OUT_GRID2D];
        p_b[OUT_GRID2D] = false;
      }
      p[OUT_CUTX] = 0;
      p_b[OUT_CUTX] = false;
      p[OUT_CUTY] = 0;
      p_b[OUT_CUTY] = false;
      p[OUT_CUTZ] = 0;
      p_b[OUT_CUTZ] = false;
    }
    if (p_b[OUT_PARAMS] && !do_not_ask_missing)
    {
      std::cout << "Do you want a .dat files with simulation parameters? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_PARAMS];
      p_b[OUT_PARAMS] = false;
    }
    if (p_b[OUT_LINEOUT_X] && !do_not_ask_missing)
    {
      std::cout << "Do you want a lineout along x? 0 (NO) - 1 (YES): ";
      std::cin >> p[OUT_LINEOUT_X];
      p_b[OUT_LINEOUT_X] = false;
    }
  }
}



bool Parametri::check_parametri()
{
  bool test = true;
  if (!p_b[SWAP] && p[SWAP] != 0 && p[SWAP] != 1)   // check swap o non-swap
  {
    printf("Warning: swap mode badly defined\n");
    test = false;
  }
  else
  {
    if (!p_b[SWAP] && (p[SWAP] == 0 || p[SWAP] == 1))
    {
      test = true;    // tutto ok, in questo caso il parametro va bene!
    }
    else if (p_b[SWAP] && do_not_ask_missing)
    {
      p[SWAP] = 0;
      p_b[SWAP] = false;
      test = true;
    }
    else
    {
      printf("Warning: swap mode undefined\n");
      test = false;
    }
  }
  if (file_particelle_P || file_particelle_E || file_particelle_HI || file_particelle_LI || file_particelle_generic_ion)
  {
    if (!p_b[WEIGHT] && p[WEIGHT] != 0 && p[WEIGHT] != 1)
    {
      printf("Warning: weight mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[WEIGHT] && (p_b[WEIGHT] == 0 || p_b[WEIGHT] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[WEIGHT] && do_not_ask_missing)
      {
        p[WEIGHT] = 1;
        p_b[WEIGHT] = false;
        test = true;
      }
      else
      {
        printf("Warning: weight mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_CSV] && p[OUT_CSV] != 0 && p[OUT_CSV] != 1)  // check leggi_particelle: out-ascii o non-out-ascii
    {
      printf("Warning: csv mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_CSV] && (p_b[OUT_CSV] == 0 || p_b[OUT_CSV] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_CSV] && do_not_ask_missing)
      {
        p[OUT_CSV] = 0;
        p_b[OUT_CSV] = false;
        test = true;
      }
      else
      {
        printf("Warning: csv mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_PROPAGA] && p[OUT_PROPAGA] != 0 && p[OUT_PROPAGA] != 1)  // check leggi_particelle: out-ascii o non-out-ascii
    {
      printf("Warning: ppg mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_PROPAGA] && (p_b[OUT_PROPAGA] == 0 || p_b[OUT_PROPAGA] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_PROPAGA] && do_not_ask_missing)
      {
        p[OUT_PROPAGA] = 0;
        p_b[OUT_PROPAGA] = false;
        test = true;
      }
      else
      {
        printf("Warning: ppg mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_XYZE] && p[OUT_XYZE] != 0 && p[OUT_XYZE] != 1)
    {
      printf("Warning: xyzE mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_XYZE] && (p_b[OUT_XYZE] == 0 || p_b[OUT_XYZE] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_XYZE] && do_not_ask_missing)
      {
        p[OUT_XYZE] = 0;
        p_b[OUT_XYZE] = false;
        test = true;
      }
      else
      {
        printf("Warning: xyzE mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_VTK] && p[OUT_VTK] != 0 && p[OUT_VTK] != 1)
    {
      printf("Warning: vtk mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_VTK] && (p[OUT_VTK] == 0 || p[OUT_VTK] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_VTK] && do_not_ask_missing)
      {
        p[OUT_VTK] = 0;
        p_b[OUT_VTK] = false;
        test = true;
      }
      else
      {
        printf("Warning: vtk mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_CLEAN_BINARY] && p[OUT_CLEAN_BINARY] != 0 && p[OUT_CLEAN_BINARY] != 1)
    {
      printf("Warning: bin mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_CLEAN_BINARY] && (p[OUT_CLEAN_BINARY] == 0 || p[OUT_CLEAN_BINARY] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_CLEAN_BINARY] && do_not_ask_missing)
      {
        p[OUT_CLEAN_BINARY] = 0;
        p_b[OUT_CLEAN_BINARY] = false;
        test = true;
      }
      else
      {
        printf("Warning: bin mode undefined\n");
        test = false;
      }
    }

    if (!p_b[FIND_MINMAX] && p[FIND_MINMAX] != 0 && p[FIND_MINMAX] != 1)
    {
      printf("Warning: min/max mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[FIND_MINMAX] && (p[FIND_MINMAX] == 0 || p[FIND_MINMAX] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[FIND_MINMAX] && do_not_ask_missing)
      {
        p[FIND_MINMAX] = 0;
        p_b[FIND_MINMAX] = false;
        test = true;
      }
      else
      {
        printf("Warning: min/max mode undefined\n");
        test = false;
      }
    }
    if (!p_b[DO_BINNING] && p[DO_BINNING] != 0 && p[DO_BINNING] != 1)
    {
      printf("Warning: binning mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[DO_BINNING] && (p[DO_BINNING] == 0 || p[DO_BINNING] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[DO_BINNING] && do_not_ask_missing)
      {
        p[DO_BINNING] = 0;
        p_b[DO_BINNING] = false;
        test = true;
      }
      else
      {
        printf("Warning: binning mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_PARAMS] && p[OUT_PARAMS] != 0 && p[OUT_PARAMS] != 1)
    {
      printf("Warning: dat mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_PARAMS] && (p[OUT_PARAMS] == 0 || p[OUT_PARAMS] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_PARAMS] && do_not_ask_missing)
      {
        p[OUT_PARAMS] = 0;
        p_b[OUT_PARAMS] = false;
        test = true;
      }
      else
      {
        printf("Warning: dat mode undefined\n");
        test = false;
      }
    }
    if (!p_b[NCOLONNE] && p[NCOLONNE] != 4 && p[NCOLONNE] != 5 && p[NCOLONNE] != 6 && p[NCOLONNE] != 7 && p[NCOLONNE] != 8)
    {
      printf("Warning: column number badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[NCOLONNE] && (p[NCOLONNE] == 4 || p[NCOLONNE] == 5 || p[NCOLONNE] == 6 || p[NCOLONNE] == 7 || p[NCOLONNE] == 8))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[NCOLONNE] && do_not_ask_missing)
      {
        p[NCOLONNE] = 8;
        p_b[NCOLONNE] = false;
        test = true;
      }
      else
      {
        printf("Warning: column number undefined\n");
        test = false;
      }
    }


    if (xmin > xmax)
    {
      printf("Warning: xmin > xmax\n");
      test = false;
    }
    if (ymin > ymax)
    {
      printf("Warning: ymin > ymax\n");
      test = false;
    }
    if (zmin > zmax)
    {
      printf("Warning: zmin > zmax\n");
      test = false;
    }
    if (pxmin > pxmax)
    {
      printf("Warning: pxmin > pxmax\n");
      test = false;
    }
    if (pymin > pymax)
    {
      printf("Warning: pymin > pymax\n");
      test = false;
    }
    if (pzmin > pzmax)
    {
      printf("Warning: pzmin > pzmax\n");
      test = false;
    }
    if (Emin > Emax)
    {
      printf("Warning: Emin > Emax\n");
      test = false;
    }
    if (thetamin > thetamax)
    {
      printf("Warning: thetamin > thetamax\n");
      test = false;
    }
    if (thetaTmin > thetaTmax)
    {
      printf("Warning: thetaTmin > thetaTmax\n");
      test = false;
    }
    if (tymin > tymax)
    {
      printf("Warning: tymin > tymax\n");
      test = false;
    }
    if (tzmin > tzmax)
    {
      printf("Warning: tzmin > tzmax\n");
      test = false;
    }
    if (wmin > wmax)
    {
      printf("Warning: wmin > wmax\n");
      test = false;
    }
    if (chmin > chmax)
    {
      printf("Warning: chmin > chmax\n");
      test = false;
    }
    if (nbin_x <= 0)
    {
      printf("Warning: nbin_x < 0\n");
      test = false;
    }
    if (nbin_y <= 0)
    {
      printf("Warning: nbin_y < 0\n");
      test = false;
    }
    if (nbin_z <= 0)
    {
      printf("Warning: nbin_z < 0\n");
      test = false;
    }
    if (nbin_px <= 0)
    {
      printf("Warning: nbin_px < 0\n");
      test = false;
    }
    if (nbin_py <= 0)
    {
      printf("Warning: nbin_py < 0\n");
      test = false;
    }
    if (nbin_pz <= 0)
    {
      printf("Warning: nbin_pz < 0\n");
      test = false;
    }
    if (nbin_E <= 0)
    {
      printf("Warning: nbin_E < 0\n");
      test = false;
    }
    if (nbin_theta <= 0)
    {
      printf("Warning: nbin_theta < 0\n");
      test = false;
    }
    if (nbin_thetaT <= 0)
    {
      printf("Warning: nbin_thetaT < 0\n");
      test = false;
    }
    if (nbin_ty <= 0)
    {
      printf("Warning: nbin_ty < 0\n");
      test = false;
    }
    if (nbin_tz <= 0)
    {
      printf("Warning: nbin_tz < 0\n");
      test = false;
    }
    if (nbin_w <= 0)
    {
      printf("Warning: nbin_w < 0\n");
      test = false;
    }
    if (nbin_ch <= 0)
    {
      printf("Warning: nbin_ch < 0\n");
      test = false;
    }
  }
  else
  {
    if (!p_b[OUT_VTK_NOSTRETCH] && p[OUT_VTK_NOSTRETCH] != 0 && p[OUT_VTK_NOSTRETCH] != 1)
    {
      printf("Warning: .vtk non-stretched badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_VTK_NOSTRETCH] && (p[OUT_VTK_NOSTRETCH] == 0 || p[OUT_VTK_NOSTRETCH] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_VTK_NOSTRETCH] && do_not_ask_missing)
      {
        p[OUT_VTK_NOSTRETCH] = 0;
        p_b[OUT_VTK_NOSTRETCH] = false;
        test = true;
      }
      else
      {
        printf("Warning: .vtk non-stretched undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_VTK] && p[OUT_VTK] != 0 && p[OUT_VTK] != 1)
    {
      printf("Warning: .vtk badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_VTK] && (p[OUT_VTK] == 0 || p[OUT_VTK] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_VTK] && do_not_ask_missing)
      {
        p[OUT_VTK] = 0;
        p_b[OUT_VTK] = false;
        test = true;
      }
      else
      {
        printf("Warning: .vtk undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_PARAMS] && p[OUT_PARAMS] != 0 && p[OUT_PARAMS] != 1)
    {
      printf("Warning: .dat parameter output badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_PARAMS] && (p[OUT_PARAMS] == 0 || p[OUT_PARAMS] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_PARAMS] && do_not_ask_missing)
      {
        p[OUT_PARAMS] = 0;
        p_b[OUT_PARAMS] = false;
        test = true;
      }
      else
      {
        printf("Warning: .dat parameter output undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_LINEOUT_X] && p[OUT_LINEOUT_X] != 0 && p[OUT_LINEOUT_X] != 1)
    {
      printf("Warning: lineout output badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_LINEOUT_X] && (p[OUT_LINEOUT_X] == 0 || p[OUT_LINEOUT_X] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_LINEOUT_X] && do_not_ask_missing)
      {
        p[OUT_LINEOUT_X] = 0;
        p_b[OUT_LINEOUT_X] = false;
        test = true;
      }
      else
      {
        printf("Warning: lineout output undefined\n");
        test = false;
      }
    }
    if (!p_b[NCOLONNE] && p[NCOLONNE] < 1)
    {
      printf("Warning: grid size badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[NCOLONNE] && p[NCOLONNE] >= 1)
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else
      {
        printf("Warning: unable to understand grid size\n");
        printf("If necessary (no .dat file available) please use -ncol at command line\n");
        test = false;
      }
    }
    if (!p_b[OUT_CUTX] && p[OUT_CUTX] != 0 && p[OUT_CUTX] != 1)
    {
      printf("Warning: slice mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_CUTX] && (p[OUT_CUTX] == 0 || p[OUT_CUTX] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_CUTX] && do_not_ask_missing)
      {
        p[OUT_CUTX] = 0;
        p_b[OUT_CUTX] = false;
        test = true;
      }
      else
      {
        printf("Warning: slice mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_CUTY] && p[OUT_CUTY] != 0 && p[OUT_CUTY] != 1)
    {
      printf("Warning: slice mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_CUTY] && (p[OUT_CUTY] == 0 || p[OUT_CUTY] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_CUTY] && do_not_ask_missing)
      {
        p[OUT_CUTY] = 0;
        p_b[OUT_CUTY] = false;
        test = true;
      }
      else
      {
        printf("Warning: slice mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_CUTZ] && p[OUT_CUTZ] != 0 && p[OUT_CUTZ] != 1)
    {
      printf("Warning: slice mode badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_CUTZ] && (p[OUT_CUTZ] == 0 || p[OUT_CUTZ] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_CUTZ] && do_not_ask_missing)
      {
        p[OUT_CUTZ] = 0;
        p_b[OUT_CUTZ] = false;
        test = true;
      }
      else
      {
        printf("Warning: slice mode undefined\n");
        test = false;
      }
    }
    if (!p_b[OUT_GRID2D] && p[OUT_GRID2D] != 0 && p[OUT_GRID2D] != 1)
    {
      printf("Warning: 2D grid output badly defined\n");
      test = false;
    }
    else
    {
      if (!p_b[OUT_GRID2D] && (p[OUT_GRID2D] == 0 || p[OUT_GRID2D] == 1))
      {
        test = true;    // tutto ok, in questo caso il parametro va bene!
      }
      else if (p_b[OUT_GRID2D] && do_not_ask_missing)
      {
        p[OUT_GRID2D] = 0;
        p_b[OUT_GRID2D] = false;
        test = true;
      }
      else
      {
        printf("Warning: 2D grid output undefined\n");
        test = false;
      }
    }
  }


  return test;
}


void Parametri::organizza_minimi_massimi()
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
  minimi[9] = thetaTmin;
  minimi[10] = tymin;
  minimi[11] = tzmin;
  minimi[12] = wmin;
  minimi[13] = chmin;

  massimi[0] = xmax;
  massimi[1] = ymax;
  massimi[2] = zmax;
  massimi[3] = pxmax;
  massimi[4] = pymax;
  massimi[5] = pzmax;
  massimi[6] = gammamax;
  massimi[7] = thetamax;
  massimi[8] = Emax;
  massimi[9] = thetaTmax;
  massimi[10] = tymax;
  massimi[11] = tzmax;
  massimi[12] = wmax;
  massimi[13] = chmax;
}

