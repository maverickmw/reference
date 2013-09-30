gromacs/src/gromacs/legacyheaders/types

!!simple.h

#define XX      0           /* Defines for indexing in	*/
#define YY      1           /* vectors			*/
#define ZZ      2
#define DIM     3           /* Dimension of vectors		*/
#define XXXX    0           /* defines to index matrices */
#define XXYY    1
#define XXZZ    2
#define YYXX    3
#define YYYY    4
#define YYZZ    5
#define ZZXX    6
#define ZZYY    7
#define ZZZZ    8

typedef int gmx_bool;

typedef int         atom_id;      /* To indicate an atoms id         */
#define NO_ATID     (atom_id)(~0) /* Use this to indicate invalid atid */

typedef real            rvec[DIM];
typedef double          dvec[DIM];
typedef real            matrix[DIM][DIM];
typedef real            tensor[DIM][DIM];
typedef int             ivec[DIM];
typedef int             imatrix[DIM][DIM];

typedef long long int gmx_large_int_t;  //64bit

// others for compiler and check later

!! atoms.h
#inlude "simple.h"

enum {
    eptAtom, eptNucleus, eptShell, eptBond, eptVSite, eptNR
};
/* The particle type */

typedef struct {
    real           m, q;        /* Mass and charge                      */
    real           mB, qB;      /* Mass and charge for Free Energy calc */
    unsigned short type;        /* Atom type                            */
    unsigned short typeB;       /* Atom type for Free Energy calc       */
    int            ptype;       /* Particle type                        */
    int            resind;      /* Index into resinfo (in t_atoms)      */
    int            atomnumber;  /* Atomic Number or NOTSET              */
    char           elem[4];     /* Element name                         */
} t_atom;

typedef struct {
    char          **name;       /* Pointer to the residue name          */
    int             nr;         /* Residue number                       */
    unsigned char   ic;         /* Code for insertion of residues       */
    int             chainnum;   /* Iincremented at TER or new chain id  */
    char            chainid;    /* Chain identifier written/read to pdb */
    char          **rtp;        /* rtp building block name (optional)   */
} t_resinfo;

typedef struct {
    int      type;              /* PDB record name                      */
    int      atomnr;            /* PDB atom number                      */
    char     altloc;            /* Alternate location indicator         */
    char     atomnm[6];         /* True atom name including leading spaces */
    real     occup;             /* Occupancy                            */
    real     bfac;              /* B-factor                             */
    gmx_bool bAnisotropic;      /* (an)isotropic switch                 */
    int      uij[6];            /* Anisotropic B-factor                 */
} t_pdbinfo;

typedef struct {
    int   nr;                   /* Number of different groups           */
    int  *nm_ind;               /* Index in the group names             */
} t_grps;

typedef struct {
    int            nr;          /* Nr of atoms                          */
    t_atom        *atom;        /* Array of atoms (dim: nr)             */
                                /* The following entries will not       */
                                /* always be used (nres==0)             */
    char          ***atomname;  /* Array of pointers to atom name       */
                                /* use: (*(atomname[i]))                */
    char          ***atomtype;  /* Array of pointers to atom types      */
                                /* use: (*(atomtype[i]))                */
    char          ***atomtypeB; /* Array of pointers to B atom types    */
                                /* use: (*(atomtypeB[i]))               */
    int              nres;      /* The number of resinfo entries        */
    t_resinfo       *resinfo;   /* Array of residue names and numbers   */
    t_pdbinfo       *pdbinfo;   /* PDB Information, such as aniso. Bfac */
} t_atoms;

typedef struct {
    int           nr;           /* number of atomtypes                          */
    real         *radius;       /* GBSA radius for each atomtype                */
    real         *vol;          /* GBSA efective volume for each atomtype       */
    real         *surftens;     /* implicit solvent surftens for each atomtype  */
    real         *gb_radius;    /* GB radius for each atom type                 */
    real         *S_hct;        /* Overlap factors for HCT/OBC GB models        */
    int          *atomnumber;   /* Atomic number, used for QM/MM                */
} t_atomtypes;

!!block.h
#include "../../utility/gmxmpi.h"
#inlcude "idef.h"

typedef struct {
    int      nr;           /* The number of blocks			*/
    atom_id *index;        /* Array of indices (dim: nr+1)  */
    int      nalloc_index; /* The allocation size for index        */
} t_block;

typedef struct {
    int      nr;    /* The number of blocks			*/
    atom_id *index; /* Array of indices in a (dim: nr+1)	*/
    int      nra;   /* The number of atoms          */
    atom_id *a;     /* Array of atom numbers in each group  */
                    /* (dim: nra)				*/
                    /* Block i (0<=i<nr) runs from		*/
                    /* index[i] to index[i+1]-1. There will */
                    /* allways be an extra entry in index	*/
                    /* to terminate the table		*/
    int nalloc_index;           /* The allocation size for index        */
    int nalloc_a;               /* The allocation size for a            */
} t_blocka;

!!commrec.h

#define DD_MAXZONE  8
#define DD_MAXIZONE 4

typedef struct gmx_domdec_master *gmx_domdec_master_p_t;

typedef struct {
    int  j0;     /* j-zone start               */
    int  j1;     /* j-zone end                 */
    int  cg1;    /* i-charge-group end         */
    int  jcg0;   /* j-charge-group start       */
    int  jcg1;   /* j-charge-group end         */
    ivec shift0; /* Minimum shifts to consider */
    ivec shift1; /* Maximum shifts to consider */
} gmx_domdec_ns_ranges_t;

typedef struct {
    rvec x0;     /* Zone lower corner in triclinic coordinates         */
    rvec x1;     /* Zone upper corner in triclinic coordinates         */
    rvec bb_x0;  /* Zone bounding box lower corner in Cartesian coords */
    rvec bb_x1;  /* Zone bounding box upper corner in Cartesian coords */
} gmx_domdec_zone_size_t;

typedef struct {
    /* The number of zones including the home zone */
    int                    n;
    /* The shift of the zones with respect to the home zone */
    ivec                   shift[DD_MAXZONE];
    /* The charge group boundaries for the zones */
    int                    cg_range[DD_MAXZONE+1];
    /* The number of neighbor search zones with i-particles */
    int                    nizone;
    /* The neighbor search charge group ranges for each i-zone */
    gmx_domdec_ns_ranges_t izone[DD_MAXIZONE];
    /* Boundaries of the zones */
    gmx_domdec_zone_size_t size[DD_MAXZONE];
    /* The cg density of the home zone */
    real                   dens_zone0;
} gmx_domdec_zones_t;

typedef struct gmx_ga2la *gmx_ga2la_t;

typedef struct gmx_hash *gmx_hash_t;

typedef struct gmx_reverse_top *gmx_reverse_top_p_t;

typedef struct gmx_domdec_constraints *gmx_domdec_constraints_p_t;

typedef struct gmx_domdec_specat_comm *gmx_domdec_specat_comm_p_t;

typedef struct gmx_domdec_comm *gmx_domdec_comm_p_t;

typedef struct gmx_pme_comm_n_box *gmx_pme_comm_n_box_p_t;

typedef struct {
    int  npbcdim;
    int  nboundeddim;
    rvec box0;
    rvec box_size;
    /* Tells if the box is skewed for each of the three cartesian directions */
    ivec tric_dir;
    rvec skew_fac;
    /* Orthogonal vectors for triclinic cells, Cartesian index */
    rvec v[DIM][DIM];
    /* Normal vectors for the cells walls */
    rvec normal[DIM];
} gmx_ddbox_t;

typedef struct {
    /* these buffers are used as destination buffers if MPI_IN_PLACE isn't
       supported.*/
    int             *ibuf; /* for ints */
    int              ibuf_alloc;

    gmx_large_int_t *libuf;
    int              libuf_alloc;

    float           *fbuf; /* for floats */
    int              fbuf_alloc;

    double          *dbuf; /* for doubles */
    int              dbuf_alloc;
} mpi_in_place_buf_t;

typedef struct {
    /* The DD particle-particle nodes only */
    /* The communication setup within the communicator all
     * defined in dd->comm in domdec.c
     */
    int                    nnodes;
    MPI_Comm               mpi_comm_all;
    /* Use MPI_Sendrecv communication instead of non-blocking calls */
    gmx_bool               bSendRecv2;
    /* The local DD cell index and rank */
    ivec                   ci;
    int                    rank;
    ivec                   master_ci;
    int                    masterrank;
    /* Communication with the PME only nodes */
    int                    pme_nodeid;
    gmx_bool               pme_receive_vir_ener;
    gmx_pme_comm_n_box_p_t cnb;
    int                    nreq_pme;
    MPI_Request            req_pme[4];


    /* The communication setup, identical for each cell, cartesian index */
    ivec     nc;
    int      ndim;
    ivec     dim; /* indexed by 0 to ndim */
    gmx_bool bGridJump;

    /* PBC from dim 0 to npbcdim */
    int npbcdim;

    /* Screw PBC? */
    gmx_bool bScrewPBC;

    /* Forward and backward neighboring cells, indexed by 0 to ndim */
    int  neighbor[DIM][2];

    /* Only available on the master node */
    gmx_domdec_master_p_t ma;

    /* Are there inter charge group constraints */
    gmx_bool bInterCGcons;
    gmx_bool bInterCGsettles;

    /* Global atom number to interaction list */
    gmx_reverse_top_p_t reverse_top;
    int                 nbonded_global;
    int                 nbonded_local;

    /* The number of inter charge-group exclusions */
    int  n_intercg_excl;

    /* Vsite stuff */
    gmx_hash_t                 ga2la_vsite;
    gmx_domdec_specat_comm_p_t vsite_comm;

    /* Constraint stuff */
    gmx_domdec_constraints_p_t constraints;
    gmx_domdec_specat_comm_p_t constraint_comm;

    /* The local to gobal charge group index and local cg to local atom index */
    int   ncg_home;
    int   ncg_tot;
    int  *index_gl;
    int  *cgindex;
    int   cg_nalloc;
    /* Local atom to local cg index, only for special cases */
    int  *la2lc;
    int   la2lc_nalloc;

    /* The number of home atoms */
    int   nat_home;
    /* The total number of atoms: home and received zones */
    int   nat_tot;
    /* Index from the local atoms to the global atoms */
    int  *gatindex;
    int   gatindex_nalloc;

    /* Global atom number to local atom number list */
    gmx_ga2la_t ga2la;

    /* Communication stuff */
    gmx_domdec_comm_p_t comm;

    /* The partioning count, to keep track of the state */
    gmx_large_int_t ddp_count;


    /* gmx_pme_recv_f buffer */
    int   pme_recv_f_alloc;
    rvec *pme_recv_f_buf;

} gmx_domdec_t;

typedef struct gmx_partdec *gmx_partdec_p_t;

typedef struct {
    int       nsim;
    int       sim;
    MPI_Group mpi_group_masters;
    MPI_Comm  mpi_comm_masters;
    /* these buffers are used as destination buffers if MPI_IN_PLACE isn't
       supported.*/
    mpi_in_place_buf_t *mpb;
} gmx_multisim_t;

#define DUTY_PP  (1<<0)
#define DUTY_PME (1<<1)

typedef struct {
    int      bUse;
    MPI_Comm comm_intra;
    int      rank_intra;
    MPI_Comm comm_inter;

} gmx_nodecomm_t;

typedef struct {
    /* The nodeids in one sim are numbered sequentially from 0.
     * All communication within some simulation should happen
     * in mpi_comm_mysim, or its subset mpi_comm_mygroup.
     */
    int sim_nodeid, nnodes, npmenodes;

    /* thread numbers: */
    /* Not used yet: int threadid, nthreads; */
    /* The nodeid in the PP/PME, PP or PME group */
    int      nodeid;
    MPI_Comm mpi_comm_mysim;
    MPI_Comm mpi_comm_mygroup;

    /* MPI ranks within a physical node for hardware access */
    int            nrank_intranode;    /* nr of ranks on this physical node */
    int            rank_intranode;     /* our rank on this physical node */
    int            nrank_pp_intranode; /* as nrank_intranode, for particle-particle only */
    int            rank_pp_intranode;  /* as rank_intranode, for particle-particle only */

    gmx_nodecomm_t nc;

    /* For domain decomposition */
    gmx_domdec_t *dd;

    /* For particle decomposition */
    gmx_partdec_p_t pd;

    /* The duties of this node, see the defines above */
    int             duty;

    gmx_multisim_t *ms;

    /* these buffers are used as destination buffers if MPI_IN_PLACE isn't
       supported.*/
    mpi_in_place_buf_t *mpb;
} t_commrec;

#define MASTERNODE(cr)     (((cr)->nodeid == 0) || !PAR(cr))
/* #define MASTERTHREAD(cr)   ((cr)->threadid == 0) */
/* #define MASTER(cr)         (MASTERNODE(cr) && MASTERTHREAD(cr)) */
#define MASTER(cr)         MASTERNODE(cr)
#define SIMMASTER(cr)      ((MASTER(cr) && ((cr)->duty & DUTY_PP)) || !PAR(cr))
#define NODEPAR(cr)        ((cr)->nnodes > 1)
/* #define THREADPAR(cr)      ((cr)->nthreads > 1) */
/* #define PAR(cr)            (NODEPAR(cr) || THREADPAR(cr)) */
#define PAR(cr)            NODEPAR(cr)
#define RANK(cr, nodeid)    (nodeid)
#define MASTERRANK(cr)     (0)

#define DOMAINDECOMP(cr)   (((cr)->dd != NULL) && PAR(cr))
#define DDMASTER(dd)       ((dd)->rank == (dd)->masterrank)

#define PARTDECOMP(cr)     ((cr)->pd != NULL)

#define MULTISIM(cr)       ((cr)->ms)
#define MSRANK(ms, nodeid)  (nodeid)
#define MASTERSIM(ms)      ((ms)->sim == 0)

/* The master of all (the node that prints the remaining run time etc.) */
#define MULTIMASTER(cr)    (SIMMASTER(cr) && (!MULTISIM(cr) || MASTERSIM((cr)->ms)))

!!constr.h    //??relay on what file??

/* Abstract type for LINCS that is defined only in the file that uses it */
typedef struct gmx_lincsdata *gmx_lincsdata_t;

/* Abstract type for SHAKE that is defined only in the file that uses it */
typedef struct gmx_shakedata *gmx_shakedata_t;

/* Abstract type for SETTLE that is defined only in the file that uses it */
typedef struct gmx_settledata *gmx_settledata_t;

/* Abstract type for constraints */
typedef struct gmx_constr *gmx_constr_t;

/* Abstract type for essential dynamics that is defined only in edsam.c */
typedef struct gmx_edsam *gmx_edsam_t;

!!energy.h
#include "simple.h"

typedef struct {
    real   e;    /* The current energy.					        */
    double eav;  /* The running average                 */
    double esum; /* The sum of energies until now.			*/
} t_energy;

!!enums.h

~key types: eintmod; gmx_table_interation; gmx_table_format; gmx_nblist_kernel_geometry; gmx_nbkernel_elec; gmx_nbkernel_vdw;gmx_nblist_interation_type;

/* note: these enums should correspond to the names in gmxlib/names.c */

enum {
    epbcXYZ, epbcNONE, epbcXY, epbcSCREW, epbcNR
};

enum {
    etcNO, etcBERENDSEN, etcNOSEHOOVER, etcYES, etcANDERSEN, etcANDERSENMASSIVE, etcVRESCALE, etcNR
}; /* yes is an alias for berendsen */

#define ETC_ANDERSEN(e) (((e) == etcANDERSENMASSIVE) || ((e) == etcANDERSEN))

enum {
    epcNO, epcBERENDSEN, epcPARRINELLORAHMAN, epcISOTROPIC, epcMTTK, epcNR
}; /* isotropic is an alias for berendsen */

/* trotter decomposition extended variable parts */
enum {
    etrtNONE, etrtNHC, etrtBAROV, etrtBARONHC, etrtNHC2, etrtBAROV2, etrtBARONHC2,
    etrtVELOCITY1, etrtVELOCITY2, etrtPOSITION, etrtSKIPALL, etrtNR
};

/* sequenced parts of the trotter decomposition */
enum {
    ettTSEQ0,  ettTSEQ1,  ettTSEQ2,  ettTSEQ3,  ettTSEQ4, ettTSEQMAX
};

enum {
    epctISOTROPIC, epctSEMIISOTROPIC, epctANISOTROPIC,
    epctSURFACETENSION, epctNR
};

enum {
    erscNO, erscALL, erscCOM, erscNR
};

enum {
    ecutsGROUP, ecutsVERLET, ecutsNR
};

/* Coulomb / VdW interaction modifiers.
 * grompp replaces eintmodPOTSHIFT_VERLET by eintmodPOTSHIFT or eintmodNONE.
 * Exactcutoff is only used by Reaction-field-zero, and is not user-selectable.
 */
enum eintmod {
    eintmodPOTSHIFT_VERLET, eintmodPOTSHIFT, eintmodNONE, eintmodPOTSWITCH, eintmodEXACTCUTOFF, eintmodNR
};

/*
 * eelNOTUSED1 used to be GB, but to enable generalized born with different
 * forms of electrostatics (RF, switch, etc.) in the future it is now selected
 * separately (through the implicit_solvent option).
 */
enum {
    eelCUT,     eelRF,     eelGRF,   eelPME,  eelEWALD,  eelP3M_AD,
    eelPOISSON, eelSWITCH, eelSHIFT, eelUSER, eelGB_NOTUSED, eelRF_NEC, eelENCADSHIFT,
    eelPMEUSER, eelPMESWITCH, eelPMEUSERSWITCH, eelRF_ZERO, eelNR
};

/* Ewald geometry */
enum {
    eewg3D, eewg3DC, eewgNR
};

#define EEL_RF(e) ((e) == eelRF || (e) == eelGRF || (e) == eelRF_NEC || (e) == eelRF_ZERO )

#define EEL_PME(e)  ((e) == eelPME || (e) == eelPMESWITCH || (e) == eelPMEUSER || (e) == eelPMEUSERSWITCH || (e) == eelP3M_AD)
#define EEL_FULL(e) (EEL_PME(e) || (e) == eelPOISSON || (e) == eelEWALD)

#define EEL_SWITCHED(e) ((e) == eelSWITCH || (e) == eelSHIFT || (e) == eelENCADSHIFT || (e) == eelPMESWITCH || (e) == eelPMEUSERSWITCH)

#define EEL_USER(e) ((e) == eelUSER || (e) == eelPMEUSER || (e) == (eelPMEUSERSWITCH))

#define EEL_IS_ZERO_AT_CUTOFF(e) (EEL_SWITCHED(e) || (e) == eelRF_ZERO)

#define EEL_MIGHT_BE_ZERO_AT_CUTOFF(e) (EEL_IS_ZERO_AT_CUTOFF(e) || (e) == eelUSER || (e) == eelPMEUSER)

enum {
    evdwCUT, evdwSWITCH, evdwSHIFT, evdwUSER, evdwENCADSHIFT, evdwNR
};

#define EVDW_SWITCHED(e) ((e) == evdwSWITCH || (e) == evdwSHIFT || (e) == evdwENCADSHIFT)

#define EVDW_IS_ZERO_AT_CUTOFF(e) EVDW_SWITCHED(e)

#define EVDW_MIGHT_BE_ZERO_AT_CUTOFF(e) (EVDW_IS_ZERO_AT_CUTOFF(e) || (e) == evdwUSER)

enum {
    ensGRID, ensSIMPLE, ensNR
};

/* eiVV is normal velocity verlet -- eiVVAK uses 1/2*(KE(t-dt/2)+KE(t+dt/2)) as the kinetic energy, and the half step kinetic
   energy for temperature control */

enum {
    eiMD, eiSteep, eiCG, eiBD, eiSD2, eiNM, eiLBFGS, eiTPI, eiTPIC, eiSD1, eiVV, eiVVAK, eiNR
};
#define EI_VV(e) ((e) == eiVV || (e) == eiVVAK)
#define EI_MD(e) ((e) == eiMD || EI_VV(e))
#define EI_SD(e) ((e) == eiSD1 || (e) == eiSD2)
#define EI_RANDOM(e) (EI_SD(e) || (e) == eiBD)
/*above integrators may not conserve momenta*/
#define EI_DYNAMICS(e) (EI_MD(e) || EI_SD(e) || (e) == eiBD)
#define EI_ENERGY_MINIMIZATION(e) ((e) == eiSteep || (e) == eiCG || (e) == eiLBFGS)
#define EI_TPI(e) ((e) == eiTPI || (e) == eiTPIC)

#define EI_STATE_VELOCITY(e) (EI_MD(e) || EI_SD(e))

enum {
    econtLINCS, econtSHAKE, econtNR
};

enum {
    edrNone, edrSimple, edrEnsemble, edrNR
};

enum {
    edrwConservative, edrwEqual, edrwNR
};

/* Combination rule things */
enum {
    eCOMB_NONE, eCOMB_GEOMETRIC, eCOMB_ARITHMETIC, eCOMB_GEOM_SIG_EPS, eCOMB_NR
};

/* NBF selection */
enum {
    eNBF_NONE, eNBF_LJ, eNBF_BHAM, eNBF_NR
};

/* simulated tempering methods */
enum {
    esimtempGEOMETRIC, esimtempEXPONENTIAL, esimtempLINEAR, esimtempNR
};
/* FEP selection */
enum {
    efepNO, efepYES, efepSTATIC, efepSLOWGROWTH, efepEXPANDED, efepNR
};
/* if efepNO, there are no evaluations at other states.
   if efepYES, treated equivalently to efepSTATIC.
   if efepSTATIC, then lambdas do not change during the simulation.
   if efepSLOWGROWTH, then the states change monotonically throughout the simulation.
   if efepEXPANDED, then expanded ensemble simulations are occuring.
 */

/* FEP coupling types */
enum {
    efptFEP, efptMASS, efptCOUL, efptVDW, efptBONDED, efptRESTRAINT, efptTEMPERATURE, efptNR
};

/* How the lambda weights are calculated:
   elamstatsMETROPOLIS = using the metropolis criteria
   elamstatsBARKER = using the Barker critera for transition weights - also called unoptimized Bennett
   elamstatsMINVAR = using Barker + minimum variance for weights
   elamstatsWL = Wang-Landu (using visitation counts)
   elamstatsWWL = Weighted Wang-Landau (using optimized gibbs weighted visitation counts)
 */
enum {
    elamstatsNO, elamstatsMETROPOLIS, elamstatsBARKER, elamstatsMINVAR, elamstatsWL, elamstatsWWL, elamstatsNR
};

#define ELAMSTATS_EXPANDED(e) ((e) > elamstatsNO)

#define EWL(e) ((e) == elamstatsWL || (e) == elamstatsWWL)

/* How moves in lambda are calculated:
   elmovemcMETROPOLIS - using the Metropolis criteria, and 50% up and down
   elmovemcBARKER - using the Barker criteria, and 50% up and down
   elmovemcGIBBS - computing the transition using the marginalized probabilities of the lambdas
   elmovemcMETGIBBS - computing the transition using the metropolized version of Gibbs (Monte Carlo Strategies in Scientific computing, Liu, p. 134)
 */
enum {
    elmcmoveNO, elmcmoveMETROPOLIS, elmcmoveBARKER, elmcmoveGIBBS, elmcmoveMETGIBBS, elmcmoveNR
};

/* how we decide whether weights have reached equilibrium
   elmceqNO - never stop, weights keep going
   elmceqYES - fix the weights from the beginning; no movement
   elmceqWLDELTA - stop when the WL-delta falls below a certain level
   elmceqNUMATLAM - stop when we have a certain number of samples at every step
   elmceqSTEPS - stop when we've run a certain total number of steps
   elmceqSAMPLES - stop when we've run a certain total number of samples
   elmceqRATIO - stop when the ratio of samples (lowest to highest) is sufficiently large
 */
enum {
    elmceqNO, elmceqYES, elmceqWLDELTA, elmceqNUMATLAM, elmceqSTEPS, elmceqSAMPLES, elmceqRATIO, elmceqNR
};

/* separate_dhdl_file selection */
enum
{
    /* NOTE: YES is the first one. Do NOT interpret this one as a gmx_bool */
    esepdhdlfileYES, esepdhdlfileNO, esepdhdlfileNR
};

/* dhdl_derivatives selection */
enum
{
    /* NOTE: YES is the first one. Do NOT interpret this one as a gmx_bool */
    edhdlderivativesYES, edhdlderivativesNO, edhdlderivativesNR
};

/* Solvent model */
enum {
    esolNO, esolSPC, esolTIP4P, esolNR
};

/* Dispersion correction */
enum {
    edispcNO, edispcEnerPres, edispcEner, edispcAllEnerPres, edispcAllEner, edispcNR
};

/* Shell types, for completion stuff */
enum {
    eshellCSH, eshellBASH, eshellZSH, eshellNR
};

/* Center of mass motion selection */
enum {
    ecmLINEAR, ecmANGULAR, ecmNO, ecmNR
};

/* New version of simulated annealing */
enum {
    eannNO, eannSINGLE, eannPERIODIC, eannNR
};

/* Implicit solvent algorithms */
enum {
    eisNO, eisGBSA, eisNR
};

/* Algorithms for calculating GB radii */
enum {
    egbSTILL, egbHCT, egbOBC, egbNR
};

enum {
    esaAPPROX, esaNO, esaSTILL, esaNR
};

/* Wall types */
enum {
    ewt93, ewt104, ewtTABLE, ewt126, ewtNR
};

/* Pull stuff */
enum {
    epullNO, epullUMBRELLA, epullCONSTRAINT, epullCONST_F, epullNR
};

enum {
    epullgDIST, epullgDIR, epullgCYL, epullgPOS, epullgDIRPBC, epullgNR
};

#define PULL_CYL(pull) ((pull)->eGeom == epullgCYL)

/* Enforced rotation groups */
enum {
    erotgISO, erotgISOPF,
    erotgPM, erotgPMPF,
    erotgRM, erotgRMPF,
    erotgRM2, erotgRM2PF,
    erotgFLEX, erotgFLEXT,
    erotgFLEX2, erotgFLEX2T,
    erotgNR
};

enum {
    erotgFitRMSD, erotgFitNORM, erotgFitPOT, erotgFitNR
};

/* QMMM */
enum {
    eQMmethodAM1, eQMmethodPM3, eQMmethodRHF,
    eQMmethodUHF, eQMmethodDFT, eQMmethodB3LYP, eQMmethodMP2, eQMmethodCASSCF, eQMmethodB3LYPLAN,
    eQMmethodDIRECT, eQMmethodNR
};

enum {
    eQMbasisSTO3G, eQMbasisSTO3G2, eQMbasis321G,
    eQMbasis321Gp, eQMbasis321dGp, eQMbasis621G,
    eQMbasis631G, eQMbasis631Gp, eQMbasis631dGp,
    eQMbasis6311G, eQMbasisNR
};

enum {
    eQMMMschemenormal, eQMMMschemeoniom, eQMMMschemeNR
};

enum {
    eMultentOptName, eMultentOptNo, eMultentOptLast, eMultentOptNR
};

/* flat-bottom posres geometries */
enum {
    efbposresZERO, efbposresSPHERE, efbposresCYLINDER, efbposresX, efbposresY, efbposresZ,
    efbposresNR
};

enum {
    eAdressOff, eAdressConst, eAdressXSplit, eAdressSphere, eAdressNR
};

enum {
    eAdressICOff, eAdressICThermoForce, eAdressICNR
};

enum {
    eAdressSITEcom, eAdressSITEcog, eAdressSITEatom, eAdressSITEatomatom, eAdressSITENR
};


/* The interactions contained in a (possibly merged) table
 * for computing electrostatic, VDW repulsion and/or VDW dispersion
 * contributions.
 */
enum gmx_table_interaction
{
    GMX_TABLE_INTERACTION_ELEC,
    GMX_TABLE_INTERACTION_VDWREP_VDWDISP,
    GMX_TABLE_INTERACTION_VDWEXPREP_VDWDISP,
    GMX_TABLE_INTERACTION_VDWDISP,
    GMX_TABLE_INTERACTION_ELEC_VDWREP_VDWDISP,
    GMX_TABLE_INTERACTION_ELEC_VDWEXPREP_VDWDISP,
    GMX_TABLE_INTERACTION_ELEC_VDWDISP,
    GMX_TABLE_INTERACTION_NR
};

/* Different formats for table data. Cubic spline tables are typically stored
 * with the four Y,F,G,H intermediate values (check tables.c for format), which
 * makes it easy to load with a single 4-way SIMD instruction too.
 * Linear tables only need one value per table point, or two if both V and F
 * are calculated. However, with SIMD instructions this makes the loads unaligned,
 * and in that case we store the data as F, D=F(i+1)-F(i), V, and then a blank value,
 * which again makes it possible to load as a single instruction.
 */
enum gmx_table_format
{
    GMX_TABLE_FORMAT_CUBICSPLINE_YFGH,
    GMX_TABLE_FORMAT_LINEAR_VF,
    GMX_TABLE_FORMAT_LINEAR_V,
    GMX_TABLE_FORMAT_LINEAR_F,
    GMX_TABLE_FORMAT_LINEAR_FDV0,
    GMX_TABLE_FORMAT_NR
};

/* Neighborlist geometry type.
 * Kernels will compute interactions between two particles,
 * 3-center water, 4-center water or coarse-grained beads.
 */
enum gmx_nblist_kernel_geometry
{
    GMX_NBLIST_GEOMETRY_PARTICLE_PARTICLE,
    GMX_NBLIST_GEOMETRY_WATER3_PARTICLE,
    GMX_NBLIST_GEOMETRY_WATER3_WATER3,
    GMX_NBLIST_GEOMETRY_WATER4_PARTICLE,
    GMX_NBLIST_GEOMETRY_WATER4_WATER4,
    GMX_NBLIST_GEOMETRY_CG_CG,
    GMX_NBLIST_GEOMETRY_NR
};

/* Types of electrostatics calculations available inside nonbonded kernels.
 * Note that these do NOT necessarily correspond to the user selections in the MDP file;
 * many interactions for instance map to tabulated kernels.
 */
enum gmx_nbkernel_elec
{
    GMX_NBKERNEL_ELEC_NONE,
    GMX_NBKERNEL_ELEC_COULOMB,
    GMX_NBKERNEL_ELEC_REACTIONFIELD,
    GMX_NBKERNEL_ELEC_CUBICSPLINETABLE,
    GMX_NBKERNEL_ELEC_GENERALIZEDBORN,
    GMX_NBKERNEL_ELEC_EWALD,
    GMX_NBKERNEL_ELEC_NR
};

/* Types of vdw calculations available inside nonbonded kernels.
 * Note that these do NOT necessarily correspond to the user selections in the MDP file;
 * many interactions for instance map to tabulated kernels.
 */
enum gmx_nbkernel_vdw
{
    GMX_NBKERNEL_VDW_NONE,
    GMX_NBKERNEL_VDW_LENNARDJONES,
    GMX_NBKERNEL_VDW_BUCKINGHAM,
    GMX_NBKERNEL_VDW_CUBICSPLINETABLE,
    GMX_NBKERNEL_VDW_NR
};
/* Types of interactions inside the neighborlist
 */
enum gmx_nblist_interaction_type
{
    GMX_NBLIST_INTERACTION_STANDARD,
    GMX_NBLIST_INTERACTION_FREE_ENERGY,
    GMX_NBLIST_INTERACTION_ADRESS,
    GMX_NBLIST_INTERACTION_NR
};

!!fcdata.h

typedef real rvec5[5];

/* Distance restraining stuff */
typedef struct {
    int      dr_weighting; /* Weighting of pairs in one restraint              */
    gmx_bool dr_bMixed;    /* Use sqrt of the instantaneous times              *
                            * the time averaged violation                      */
    real     dr_fc;        /* Force constant for disres,                       *
                            * which is multiplied by a (possibly)              *
                            * different factor for each restraint              */
    real  dr_tau;          /* Time constant for disres		          */
    real  ETerm;           /* multiplication factor for time averaging         */
    real  ETerm1;          /* 1 - ETerm1                                       */
    real  exp_min_t_tau;   /* Factor for slowly switching on the force         */
    int   nres;            /* The number of distance restraints                */
    int   npair;           /* The number of distance restraint pairs           */
    real  sumviol;         /* The sum of violations                            */
    real *rt;              /* The calculated instantaneous distance (npr)      */
    real *rm3tav;          /* The calculated time averaged distance (npr)      */
    real *Rtl_6;           /* The calculated instantaneous r^-6 (nr)           */
    real *Rt_6;            /* The calculated inst. ens. averaged r^-6 (nr)     */
    real *Rtav_6;          /* The calculated time and ens. averaged r^-6 (nr)  */
    int   nsystems;        /* The number of systems for ensemble averaging     */
} t_disresdata;


/* Orientation restraining stuff */
typedef struct {
    real      fc;            /* Force constant for the restraints                  */
    real      edt;           /* Multiplication factor for time averaging           */
    real      edt_1;         /* 1 - edt                                            */
    real      exp_min_t_tau; /* Factor for slowly switching on the force         */
    int       nr;            /* The number of orientation restraints               */
    int       nex;           /* The number of experiments                          */
    int       nref;          /* The number of atoms for the fit                    */
    real     *mref;          /* The masses of the reference atoms                  */
    rvec     *xref;          /* The reference coordinates for the fit (nref)       */
    rvec     *xtmp;          /* Temporary array for fitting (nref)                 */
    matrix    R;             /* Rotation matrix to rotate to the reference coor.   */
    tensor   *S;             /* Array of order tensors for each experiment (nexp)  */
    rvec5    *Dinsl;         /* The order matrix D for all restraints (nr x 5)     */
    rvec5    *Dins;          /* The ensemble averaged D (nr x 5)                   */
    rvec5    *Dtav;          /* The time and ensemble averaged D (nr x 5)          */
    real     *oinsl;         /* The calculated instantaneous orientations          */
    real     *oins;          /* The calculated emsemble averaged orientations      */
    real     *otav;          /* The calculated time and ensemble averaged orient.  */
    real      rmsdev;        /* The weighted (using kfac) RMS deviation            */
    rvec5    *tmp;           /* An array of temporary 5-vectors (nex);             */
    real   ***TMP;           /* An array of temporary 5x5 matrices (nex);          */
    real     *eig;           /* Eigenvalues/vectors, for output only (nex x 12)    */

    /* variables for diagonalization with diagonalize_orires_tensors()*/
    double **M;
    double  *eig_diag;
    double **v;
} t_oriresdata;

/*
 * Data struct used in the force calculation routines
 * for storing the tables for bonded interactions and
 * for storing information which is needed in following steps
 * (for instance for time averaging in distance retraints)
 * or for storing output, since force routines only return the potential.
 */
typedef struct {
    bondedtable_t *bondtab;
    bondedtable_t *angletab;
    bondedtable_t *dihtab;

    t_disresdata   disres;
    t_oriresdata   orires;
} t_fcdata;

!!filenm.h

enum {
    efMDP, efGCT,
    efTRX, efTRO, efTRN, efTRR, efTRJ, efXTC, efG87,
    efEDR,
    efSTX, efSTO, efGRO, efG96, efPDB, efBRK, efENT, efESP, efPQR, efXYZ,
    efCPT,
    efLOG, efXVG, efOUT,
    efNDX,
    efTOP, efITP,
    efTPX, efTPS, efTPR, efTPA, efTPB,
    efTEX, efRTP, efATP, efHDB,
    efDAT, efDLG,
    efMAP, efEPS, efMAT, efM2P,
    efMTX,
    efEDI,
    efHAT,
    efCUB,
    efXPM,
    efRND,
    efNR
};

typedef struct {
    int           ftp;    /* File type (see enum above)		*/
    const char   *opt;    /* Command line option			*/
    const char   *fn;     /* File name (as set in source code)	*/
    unsigned long flag;   /* Flag for all kinds of info (see defs)*/
    int           nfiles; /* number of files			*/
    char        **fns;    /* File names				*/
} t_filenm;

#define ffSET   1<<0
#define ffREAD  1<<1
#define ffWRITE 1<<2
#define ffOPT   1<<3
#define ffLIB   1<<4
#define ffMULT  1<<5
#define ffRW    (ffREAD | ffWRITE)
#define ffOPTRD (ffREAD | ffOPT)
#define ffOPTWR (ffWRITE| ffOPT)
#define ffOPTRW (ffRW   | ffOPT)
#define ffLIBRD (ffREAD | ffLIB)
#define ffLIBOPTRD (ffOPTRD | ffLIB)
#define ffRDMULT   (ffREAD  | ffMULT)
#define ffOPTRDMULT   (ffRDMULT | ffOPT)
#define ffWRMULT   (ffWRITE  | ffMULT)
#define ffOPTWRMULT   (ffWRMULT | ffOPT)

!!force_flags.h

/* The state has changed */
#define GMX_FORCE_STATECHANGED (1<<0)
/* The box might have changed */
#define GMX_FORCE_DYNAMICBOX   (1<<1)
/* Do neighbor searching */
#define GMX_FORCE_NS           (1<<2)
/* Update long-range neighborlists */
#define GMX_FORCE_LRNS         (1<<3)
/* Calculate bonded energies/forces */
#define GMX_FORCE_BONDED       (1<<4)
/* Store long-range forces in a separate array */
#define GMX_FORCE_SEPLRF       (1<<5)
/* Calculate non-bonded energies/forces */
#define GMX_FORCE_NONBONDED    (1<<6)
/* Calculate forces (not only energies) */
#define GMX_FORCE_FORCES       (1<<7)
/* Calculate the virial */
#define GMX_FORCE_VIRIAL       (1<<8)
/* Calculate energies */
#define GMX_FORCE_ENERGY       (1<<9)
/* Calculate dHdl */
#define GMX_FORCE_DHDL         (1<<10)
/* Calculate long-range energies/forces */
#define GMX_FORCE_DO_LR        (1<<11)

/* Normally one want all energy terms and forces */
#define GMX_FORCE_ALLFORCES    (GMX_FORCE_BONDED | GMX_FORCE_NONBONDED | GMX_FORCE_FORCES)










































