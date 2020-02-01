/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Lucida Mac:size=15" };
static const char dmenufont[]       = "Lucida Mac:size=25";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#0099CC";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance    title       tags mask     isfloating   monitor */
	{ "Gimp",                NULL,       NULL,       1,            1,           -1 },
	{ "Firefox",             NULL,       NULL,       1<<8,         0,           -1 },
	{ "netease-cloud-music", NULL,       NULL,       4<<8,         1,           -1 },
	{ "ss-qt5",              NULL,       NULL,       4<<8,         1,           -1 },
	{ "Connection Manager",  NULL,       NULL,       4<<8,         1,           -1 },
	{ "qq",                  NULL,       NULL,       4<<8,         1,           -1 },
	{ "QQ",                  NULL,       NULL,       4<<8,            1,           -1 },
	{ "Transmission",        NULL,       NULL,       4<<8,            1,           -1 },
	{ "uGet",                NULL,       NULL,       4<<8,            1,           -1 },
	{ "GoldenDict",          NULL,       NULL,       4<<8,            1,           -1 },
	{ "Steam",               NULL,       NULL,       4<<8,            1,           -1 },
	{ "Friends List",        NULL,       NULL,       4<<8,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY    Mod4Mask  // SUPER
#define ALTKEY    Mod1Mask  // Mod1Mask as alt
#define VOLMUTE   0x1008ff12
#define VOLDOWM   0x1008ff11
#define VOLUP     0x1008ff13
#define LIGHTDOWN 0x1008ff03
#define LIGHTUP   0x1008ff02
#define LOCK      0xffc6
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "chromium", NULL };
static const char *trayercmd[]  = { "/usr/ring/scripts/tr-toggle.sh", NULL };
static const char *emojicmd[]  = { "/usr/ring/scripts/dmenu-emoji-selection.sh", NULL };
static const char *wpccmd[]  = { "/usr/ring/scripts/wp-change.sh", NULL };
static const char *lockon[]  = { "xscreensaver-command --lock", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
// control 
static const char *upvol[] = {"pamixer", "-i",  "7", NULL};
static const char *dowmvol[] = {"pamixer", "-d",  "7", NULL};
static const char *mutevol[] = {"pamixer", "-t", NULL};
static const char *lightup[] = {"xbacklight", "-inc", "5", NULL};
static const char *lightdowm[] = {"xbacklight", "-dec", "5", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = trayercmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = wpccmd       } },
	{ 0,                            VOLMUTE,   spawn,          {.v = mutevol       } },
	{ 0,                            VOLDOWM,   spawn,          {.v = dowmvol       } },
	{ 0,                            VOLUP,     spawn,          {.v = upvol         } },
	{ 0,                            LIGHTDOWN ,spawn,          {.v = lightdowm     } },
	{ 0,                            LIGHTUP,   spawn,          {.v = lightup       } },
	{ 0,                            LOCK,      spawn,          {.v = lockon       } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emojicmd       } },
    // hide bar
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
    // reverse window
	//{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_l,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_r,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_h,      hidewin,        {0} },
	{ MODKEY|ShiftMask,             XK_h,      restorewin,     {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    // size control
    { MODKEY,					    XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
    { MODKEY,					    XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
    { MODKEY,					    XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
    { MODKEY,					    XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
    { MODKEY|ShiftMask,			    XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
    { MODKEY|ShiftMask,			    XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
    { MODKEY|ShiftMask,			    XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
    { MODKEY|ShiftMask,			    XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},
    { MODKEY|ShiftMask|ControlMask, XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 75 }}},
    { MODKEY|ShiftMask|ControlMask, XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -75 }}},
    { MODKEY|ShiftMask|ControlMask, XK_Right,	moveresize,		{.v = (int []){ 0, 0, 75, 0 }}},
    { MODKEY|ShiftMask|ControlMask, XK_Left,	moveresize,		{.v = (int []){ 0, 0, -75, 0 }}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

