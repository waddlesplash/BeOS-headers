#ifndef _BE_BUILD_H
#define _BE_BUILD_H


#if defined(__powerc) || defined(powerc)
	#define _PR2_COMPATIBLE_ 1
#else
	#define _PR2_COMPATIBLE_ 0
#endif


#if _STATIC_LINKING

#define _EXPORT
#define _IMPORT
#define _IMPEXP_KERNEL
#define	_IMPEXP_DRIVER
#define	_IMPEXP_FS
#define	_IMPEXP_GRAPHICS
#define	_IMPEXP_GL
#define	_IMPEXP_ROOT
#define	_IMPEXP_NET
#define	_IMPEXP_NETDEV
#define	_IMPEXP_ATALK
#define	_IMPEXP_BE
#define	_IMPEXP_TRACKER
#define	_IMPEXP_MAIL
#define	_IMPEXP_DEVICE
#define	_IMPEXP_MEDIA
#define	_IMPEXP_MIDI
#define _IMPEXP_GAME
#define _IMPEXP_TRANSLATION
#define	_IMP_ROOT

#else

#if __INTEL__

#define	_EXPORT			__declspec(dllexport)
#define	_IMPORT			__declspec(dllimport)

#if _BUILDING_kernel
#define	_IMPEXP_KERNEL	__declspec(dllexport)
#else
#define	_IMPEXP_KERNEL	__declspec(dllimport)
#endif

#if _BUILDING_driver
#define	_IMPEXP_DRIVER	__declspec(dllexport)
#else
#define	_IMPEXP_DRIVER	__declspec(dllimport)
#endif

#if _BUILDING_fs
#define	_IMPEXP_FS		__declspec(dllexport)
#else
#define	_IMPEXP_FS		__declspec(dllimport)
#endif

#if _BUILDING_graphics
#define	_IMPEXP_GRAPHICS	__declspec(dllexport)
#else
#define	_IMPEXP_GRAPHICS	__declspec(dllimport)
#endif

#if _BUILDING_root
#define	_IMPEXP_ROOT	__declspec(dllexport)
#define	_IMP_ROOT
#else
#define	_IMPEXP_ROOT	__declspec(dllimport)
#define	_IMP_ROOT		__declspec(dllimport)
#endif

#if _BUILDING_net
#define	_IMPEXP_NET		__declspec(dllexport)
#else
#define	_IMPEXP_NET		__declspec(dllimport)
#endif

#if _BUILDING_netdev
#define	_IMPEXP_NETDEV	__declspec(dllexport)
#else
#define	_IMPEXP_NETDEV	__declspec(dllimport)
#endif

#if _BUILDING_atalk
#define	_IMPEXP_ATALK	__declspec(dllexport)
#else
#define	_IMPEXP_ATALK	__declspec(dllimport)
#endif

#if _BUILDING_be
#define	_IMPEXP_BE		__declspec(dllexport)
#else
#define	_IMPEXP_BE		__declspec(dllimport)
#endif

#if _BUILDING_gl
#define	_IMPEXP_GL		__declspec(dllexport)
#else
#define	_IMPEXP_GL		__declspec(dllimport)
#endif

#if _BUILDING_tracker
#define	_IMPEXP_TRACKER	__declspec(dllexport)
#else
#define	_IMPEXP_TRACKER	__declspec(dllimport)
#endif

#if _BUILDING_mail
#define	_IMPEXP_MAIL	__declspec(dllexport)
#else
#define	_IMPEXP_MAIL	__declspec(dllimport)
#endif

#if _BUILDING_device
#define	_IMPEXP_DEVICE	__declspec(dllexport)
#else
#define	_IMPEXP_DEVICE	__declspec(dllimport)
#endif

#if _BUILDING_media
#define	_IMPEXP_MEDIA	__declspec(dllexport)
#else
#define	_IMPEXP_MEDIA	__declspec(dllimport)
#endif

#if _BUILDING_midi
#define	_IMPEXP_MIDI	__declspec(dllexport)
#else
#define	_IMPEXP_MIDI	__declspec(dllimport)
#endif

#if _BUILDING_game
#define	_IMPEXP_GAME	__declspec(dllexport)
#else
#define	_IMPEXP_GAME	__declspec(dllimport)
#endif

#if _BUILDING_translation
#define _IMPEXP_TRANSLATION	__declspec(dllexport)
#else
#define _IMPEXP_TRANSLATION	__declspec(dllimport)
#endif

#endif /* __INTEL__ */

#if __POWERPC__

#define	_EXPORT
#define	_IMPORT

#define _IMPEXP_KERNEL
#define	_IMPEXP_DRIVER
#define	_IMPEXP_FS
#define	_IMPEXP_GRAPHICS
#define	_IMPEXP_GL
#define	_IMPEXP_ROOT
#define	_IMPEXP_NET
#define	_IMPEXP_NETDEV
#define	_IMPEXP_ATALK
#define	_IMPEXP_BE
#define	_IMPEXP_TRACKER
#define	_IMPEXP_MAIL
#define	_IMPEXP_DEVICE
#define	_IMPEXP_MEDIA
#define	_IMPEXP_MIDI
#define	_IMPEXP_GAME
#define _IMPEXP_TRANSLATION
#define	_IMP_ROOT

#endif

#if __SH__

#define	_EXPORT
#define	_IMPORT

#define _IMPEXP_KERNEL
#define	_IMPEXP_DRIVER
#define	_IMPEXP_FS
#define	_IMPEXP_GRAPHICS
#define	_IMPEXP_GL
#define	_IMPEXP_ROOT
#define	_IMPEXP_NET
#define	_IMPEXP_NETDEV
#define	_IMPEXP_ATALK
#define	_IMPEXP_BE
#define	_IMPEXP_TRACKER
#define	_IMPEXP_MAIL
#define	_IMPEXP_DEVICE
#define	_IMPEXP_MEDIA
#define	_IMPEXP_MIDI
#define	_IMPEXP_GAME
#define _IMPEXP_TRANSLATION
#define	_IMP_ROOT

#endif

#endif


#ifdef __cplusplus

/* cpp kit */

/* -- <typeinfo> */
class _IMPEXP_ROOT bad_cast;
class _IMPEXP_ROOT bad_typeid;
class _IMPEXP_ROOT type_info;

/* -- <exception> */
class _IMPEXP_ROOT exception;
class _IMPEXP_ROOT bad_exception;

/* -- <new.h> */
class _IMPEXP_ROOT bad_alloc;

/* -- <mexcept.h> */
class _IMPEXP_ROOT logic_error;
class _IMPEXP_ROOT domain_error;
class _IMPEXP_ROOT invalid_argument;
class _IMPEXP_ROOT length_error;
class _IMPEXP_ROOT out_of_range;
class _IMPEXP_ROOT runtime_error;
class _IMPEXP_ROOT range_error;
class _IMPEXP_ROOT overflow_error;

/* support kit */
class _IMPEXP_BE BArchivable;
class _IMPEXP_BE BAutolock;
class _IMPEXP_BE BBlockCache;
class _IMPEXP_BE BDataIO;
class _IMPEXP_BE BPositionIO;
class _IMPEXP_BE BMallocIO;
class _IMPEXP_BE BMemoryIO;
class _IMPEXP_BE BFlattenable;
class _IMPEXP_BE BList;
class _IMPEXP_BE BLocker;
class _IMPEXP_BE BStopWatch;

class _IMPEXP_BE PointerList;

/*storage kit */
struct _IMPEXP_BE entry_ref;
struct _IMPEXP_BE node_ref;
class _IMPEXP_BE BAppFileInfo;
class _IMPEXP_BE BDirectory;
class _IMPEXP_BE BEntry;
class _IMPEXP_BE BFile;
class _IMPEXP_BE BRefFilter;
class _IMPEXP_BE BMimeType;
class _IMPEXP_BE BNode;
class _IMPEXP_BE BNodeInfo;
class _IMPEXP_BE BPath;
class _IMPEXP_BE BQuery;
class _IMPEXP_BE BResources;
class _IMPEXP_BE BStatable;
class _IMPEXP_BE BSymLink;
class _IMPEXP_BE BVolume;
class _IMPEXP_BE BVolumeRoster;

class _IMPEXP_BE Partition;
class _IMPEXP_BE Session;
class _IMPEXP_BE Device;
class _IMPEXP_BE DeviceList;
class _IMPEXP_BE TNodeWalker;
class _IMPEXP_BE TQueryWalker;
class _IMPEXP_BE TVolWalker;

/*app kit */
struct _IMPEXP_BE app_info;
class _IMPEXP_BE BApplication;
class _IMPEXP_BE BClipboard;
class _IMPEXP_BE BHandler;
class _IMPEXP_BE BInvoker;
class _IMPEXP_BE BLooper;
class _IMPEXP_BE BMessage;
class _IMPEXP_BE BMessageFilter;
class _IMPEXP_BE BMessageQueue;
class _IMPEXP_BE BMessenger;
class _IMPEXP_BE BPropertyInfo;
class _IMPEXP_BE BRoster;

class _IMPEXP_BE _BAppServerLink_;
class _IMPEXP_BE _BSession_;

/*interface kit */
class _IMPEXP_BE BAlert;
class _IMPEXP_BE BBitmap;
class _IMPEXP_BE BBox;
class _IMPEXP_BE BButton;
class _IMPEXP_BE BCheckBox;
class _IMPEXP_BE BColorControl;
class _IMPEXP_BE BControl;
class _IMPEXP_BE BDragger;
class _IMPEXP_BE BFont;
class _IMPEXP_BE BListItem;
class _IMPEXP_BE BListView;
class _IMPEXP_BE BStringItem;
class _IMPEXP_BE BMenu;
class _IMPEXP_BE BMenuBar;
class _IMPEXP_BE BMenuField;
class _IMPEXP_BE BMenuItem;
class _IMPEXP_BE BOutlineListView;
class _IMPEXP_BE BPicture;
class _IMPEXP_BE BPictureButton;
class _IMPEXP_BE BPoint;
class _IMPEXP_BE BPolygon;
class _IMPEXP_BE BPopUpMenu;
class _IMPEXP_BE BPrintJob;
class _IMPEXP_BE BRadioButton;
class _IMPEXP_BE BRect;
class _IMPEXP_BE BRegion;
class _IMPEXP_BE BScreen;
class _IMPEXP_BE BScrollBar;
class _IMPEXP_BE BScrollView;
class _IMPEXP_BE BSeparatorItem;
class _IMPEXP_BE BShelf;
class _IMPEXP_BE BSlider;
class _IMPEXP_BE BStatusBar;
class _IMPEXP_BE BStringView;
class _IMPEXP_BE BTab;
class _IMPEXP_BE BTabView;
class _IMPEXP_BE BTextControl;
class _IMPEXP_BE BTextView;
class _IMPEXP_BE BView;
class _IMPEXP_BE BWindow;

class _IMPEXP_BE _BTextInput_;
class _IMPEXP_BE _BMCMenuBar_;
class _IMPEXP_BE _BWidthBuffer_;
class _IMPEXP_BE BPrivateScreen;

/* net kit */
class _IMPEXP_NET _Allocator;
class _IMPEXP_NET _Transacter;
class _IMPEXP_NET _FastIPC;

/* netdev kit */
class _IMPEXP_NETDEV BNetPacket;
class _IMPEXP_NETDEV BStandardPacket;
class _IMPEXP_NETDEV BTimeoutHandler;
class _IMPEXP_NETDEV BPacketHandler;
class _IMPEXP_NETDEV BNetProtocol;
class _IMPEXP_NETDEV BNetDevice;
class _IMPEXP_NETDEV BCallbackHandler;
class _IMPEXP_NETDEV BNetConfig;
class _IMPEXP_NETDEV BIpDevice;

class _IMPEXP_NETDEV _NetBufList;
class _IMPEXP_NETDEV _BSem;

/* atalk kit */
class _IMPEXP_ATALK _PrinterNode;

/* tracker kit */
class _IMPEXP_TRACKER BFilePanel;
class _IMPEXP_TRACKER BNavMenu;

class _IMPEXP_TRACKER CopyLoopControl;

/* mail kit */
class _IMPEXP_MAIL	BMailMessage;

/* device kit */
class _IMPEXP_DEVICE	BA2D;
class _IMPEXP_DEVICE	BD2A;
class _IMPEXP_DEVICE	BDigitalPort;
class _IMPEXP_DEVICE	BJoystick;
class _IMPEXP_DEVICE	BSerialPort;

/* media kit */
class _IMPEXP_MEDIA 	BAVISource;
class _IMPEXP_MEDIA		BAVIRenderer;
class _IMPEXP_MEDIA		BAudioEvent;
class _IMPEXP_MEDIA		BDACRenderer;
class _IMPEXP_MEDIA		BAudioFileStream;
class _IMPEXP_MEDIA		BADCStream;
class _IMPEXP_MEDIA		BDACStream;
class _IMPEXP_MEDIA		BAbstractBufferStream;
class _IMPEXP_MEDIA		BBufferStreamManager;
class _IMPEXP_MEDIA		BBufferStream;
class _IMPEXP_MEDIA		BMediaEvent;
class _IMPEXP_MEDIA		BEventStream;
class _IMPEXP_MEDIA		BSoundFile;
class _IMPEXP_MEDIA		BSubscriber;
class _IMPEXP_MEDIA		BVideoEvent;
class _IMPEXP_MEDIA		BVideoRenderer;
class _IMPEXP_MEDIA		BVideoFileStream;
class _IMPEXP_MEDIA		BBt848Stream;
class _IMPEXP_MEDIA		BFilmStripRenderer;

/* midi kit */
class _IMPEXP_MIDI 		BMidi;
class _IMPEXP_MIDI 		BMidiPort;
class _IMPEXP_MIDI		BMidiStore;
class _IMPEXP_MIDI		BMidiSynth;
class _IMPEXP_MIDI		BMidiSynthFile;
class _IMPEXP_MIDI		BMidiText;
class _IMPEXP_MIDI		BSamples;
class _IMPEXP_MIDI		BSynth;

/* game kit */
class _IMPEXP_GAME		BWindowScreen;
class _IMPEXP_GAME		BDirectWindow;

/* translation kit */
class _IMPEXP_TRANSLATION	BTranslatorRoster;
class _IMPEXP_TRANSLATION	BTranslationUtils;
class _IMPEXP_TRANSLATION	BBitmapStream;
struct _IMPEXP_TRANSLATION	translation_format;
struct _IMPEXP_TRANSLATION	translator_info;

/* GL */
class _IMPEXP_GL BGLView;
class _IMPEXP_GL BGLScreen;
#ifdef __cplusplus
class _IMPEXP_GL GLUnurbs;
class _IMPEXP_GL GLUquadric;
class _IMPEXP_GL GLUtesselator;
#else
typedef struct _IMPEXP_GL GLUnurbs GLUnurbs;
typedef struct _IMPEXP_GL GLUquadric GLUquadric;
typedef struct _IMPEXP_GL GLUtesselator GLUtesselator;
#endif
typedef struct _IMPEXP_GL GLUnurbs GLUnurbsObj;
typedef struct _IMPEXP_GL GLUquadric GLUquadricObj;
typedef struct _IMPEXP_GL GLUtesselator GLUtesselatorObj;
typedef struct _IMPEXP_GL GLUtesselator GLUtriangulatorObj;

#endif		/* __cplusplus */

#endif
