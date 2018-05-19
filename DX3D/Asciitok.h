//************************************************************************** 
//* Asciitok.h	- Ascii File Exporter
//* 
//* By Christer Janson
//* Kinetix Development
//*
//* January 20, 1997 CCJ Initial coding
//*
//* File format tokens
//*
//* Copyright (c) 1997, All Rights Reserved. 
//***************************************************************************
/*********************************************************************************
REVISION LOG ENTRY
Revision By: rjc
Revised on 06/29/2000 11:18:37 AM
Comments:  rjc 29 jun 2000 :  Making changes and upgrades for v3.1
*********************************************************************************/
#pragma once

/**********************************************************************
 This is a list of all output tokens

 Note to translators:
 The strings in this module defines the file format and should not be
 translated.
***********************************************************************/

// Top level category ID's
#define ID_SCENE				("*SCENE")
#define ID_GEOMETRY				("*GEOMOBJECT") 
#define ID_SHAPE				("*SHAPEOBJECT") 
#define ID_CAMERA				("*CAMERAOBJECT") 
#define ID_LIGHT				("*LIGHTOBJECT") 
#define ID_HELPER				("*HELPEROBJECT")
#define ID_MATERIAL_LIST		("*MATERIAL_LIST")

// Hierarchy
#define ID_GROUP				("*GROUP")

// Node related ID's
#define ID_NODE_TM				("*NODE_TM")
#define ID_NODE_NAME			("*NODE_NAME") 
#define ID_NODE_PARENT			("*NODE_PARENT")

// Object (node) properties
#define ID_PROP_MOTIONBLUR		("*PROP_MOTIONBLUR")
#define ID_PROP_CASTSHADOW		("*PROP_CASTSHADOW")
#define ID_PROP_RECVSHADOW		("*PROP_RECVSHADOW")

// Mesh related ID's
#define ID_MESH					("*MESH")
#define ID_MESH_NORMALS			("*MESH_NORMALS") 
#define ID_MESH_NUMVERTEX		("*MESH_NUMVERTEX") 
#define ID_MESH_NUMFACES		("*MESH_NUMFACES") 
#define ID_MESH_VERTEX_LIST		("*MESH_VERTEX_LIST") 
#define ID_MESH_VERTEX			("*MESH_VERTEX")
#define ID_MESH_FACE_LIST		("*MESH_FACE_LIST") 
#define ID_MESH_FACE			("*MESH_FACE")
#define ID_MESH_SMOOTHING		("*MESH_SMOOTHING") 
#define ID_MESH_MTLID			("*MESH_MTLID")

#define ID_MESH_NUMTVERTEX		("*MESH_NUMTVERTEX") 
#define ID_MESH_NUMTVFACES		("*MESH_NUMTVFACES") 
#define ID_MESH_TVERTLIST		("*MESH_TVERTLIST") 
#define ID_MESH_TVERT			("*MESH_TVERT") 
#define ID_MESH_TFACELIST		("*MESH_TFACELIST") 
#define ID_MESH_TFACE			("*MESH_TFACE")

#define ID_MESH_NUMCVERTEX		("*MESH_NUMCVERTEX")
#define ID_MESH_NUMCVFACES		("*MESH_NUMCVFACES") 
#define ID_MESH_CVERTLIST		("*MESH_CVERTLIST")
#define ID_MESH_VERTCOL			("*MESH_VERTCOL")
#define ID_MESH_CFACELIST		("*MESH_CFACELIST")
#define ID_MESH_CFACE			("*MESH_CFACE")


#define ID_MESH_FACEMAPLIST		("*MESH_FACEMAPLIST") 
#define ID_MESH_FACEMAP			("*MESH_FACEMAP") 
#define ID_MESH_FACEVERT		("*MESH_FACEMAPVERT")

#define ID_MESH_FACENORMAL		("*MESH_FACENORMAL") 
#define ID_MESH_VERTEXNORMAL	("*MESH_VERTEXNORMAL")

#define ID_MESH_ANIMATION		("*MESH_ANIMATION")

// Shape ID's
#define ID_SHAPE_LINECOUNT		("*SHAPE_LINECOUNT") 
#define ID_SHAPE_LINE			("*SHAPE_LINE")
#define ID_SHAPE_VERTEX_KNOT	("*SHAPE_VERTEX_KNOT") 
#define ID_SHAPE_VERTEX_INTERP	("*SHAPE_VERTEX_INTERP") 
#define ID_SHAPE_VERTEXCOUNT	("*SHAPE_VERTEXCOUNT") 
#define ID_SHAPE_CLOSED			("*SHAPE_CLOSED")

// Light ID's
#define ID_LIGHT_SETTINGS		("*LIGHT_SETTINGS") 
#define ID_LIGHT_TYPE			("*LIGHT_TYPE") 
#define ID_LIGHT_COLOR			("*LIGHT_COLOR") 
#define ID_LIGHT_INTENS			("*LIGHT_INTENS") 
#define ID_LIGHT_HOTSPOT		("*LIGHT_HOTSPOT") 
#define ID_LIGHT_FALLOFF		("*LIGHT_FALLOFF") 
#define ID_LIGHT_ATTNSTART		("*LIGHT_ATTNSTART") 
#define ID_LIGHT_ATTNEND		("*LIGHT_ATTNEND")
#define ID_LIGHT_ASPECT			("*LIGHT_ASPECT")
#define ID_LIGHT_SHADOWS		("*LIGHT_SHADOWS")
#define ID_LIGHT_USELIGHT		("*LIGHT_USELIGHT")
#define ID_LIGHT_SPOTSHAPE		("*LIGHT_SPOTSHAPE")
#define ID_LIGHT_TDIST			("*LIGHT_TDIST")
#define ID_LIGHT_MAPBIAS		("*LIGHT_MAPBIAS")
#define ID_LIGHT_MAPRANGE		("*LIGHT_MAPRANGE")
#define ID_LIGHT_MAPSIZE		("*LIGHT_MAPSIZE")
#define ID_LIGHT_RAYBIAS		("*LIGHT_RAYBIAS")
#define ID_LIGHT_USEGLOBAL		("*LIGHT_USEGLOBAL")
#define ID_LIGHT_ABSMAPBIAS		("*LIGHT_ABSMAPBIAS")
#define ID_LIGHT_OVERSHOOT		("*LIGHT_OVERSHOOT")
#define ID_LIGHT_EXCLUSIONLIST	("*LIGHT_EXCLUDELIST")
#define ID_LIGHT_NUMEXCLUDED	("*LIGHT_NUMEXCLUDED")
#define ID_LIGHT_EXCLUDED		("*LIGHT_EXCLUDED")
#define ID_LIGHT_EXCLINCLUDE	("*LIGHT_EXCLUDED_INCLUDE")
#define ID_LIGHT_EXCL_AFFECT_ILLUM	("*LIGHT_EXCLUDED_AFFECT_ILLUM")
#define ID_LIGHT_EXCL_AFFECT_SHAD	("*LIGHT_EXCLUDED_AFFECT_SHADOW")
#define ID_LIGHT_ANIMATION		("*LIGHT_ANIMATION")

#define ID_LIGHT_TYPE_OMNI		("Omni")
#define ID_LIGHT_TYPE_TARG		("Target")
#define ID_LIGHT_TYPE_DIR		("Directional")
#define ID_LIGHT_TYPE_FREE		("Free")

#define ID_LIGHT_SHAD_OFF		("Off")
#define ID_LIGHT_SHAD_MAP		("Mapped")
#define ID_LIGHT_SHAD_RAY		("Raytraced")

#define ID_LIGHT_SHAPE_CIRC		("Circle")
#define ID_LIGHT_SHAPE_RECT		("Rect")

// Camera ID's
#define ID_CAMERA_SETTINGS		("*CAMERA_SETTINGS")
#define ID_CAMERA_HITHER		("*CAMERA_HITHER") 
#define ID_CAMERA_YON			("*CAMERA_YON") 
#define ID_CAMERA_NEAR			("*CAMERA_NEAR") 
#define ID_CAMERA_FAR			("*CAMERA_FAR") 
#define ID_CAMERA_FOV			("*CAMERA_FOV") 
#define ID_CAMERA_TDIST			("*CAMERA_TDIST")
#define ID_CAMERA_ANIMATION		("*CAMERA_ANIMATION")

#define ID_CAMERA_TYPE			("*CAMERA_TYPE")
#define ID_CAMERATYPE_TARGET	("Target")
#define ID_CAMERATYPE_FREE		("Free")

// Helper objects
#define ID_HELPER_CLASS			("*HELPER_CLASS")

// Controller ID's
#define ID_CONTROL_POINT3_TCB		("*CONTROL_POINT3_TCB") 
#define ID_CONTROL_POINT3_BEZIER	("*CONTROL_POINT3_BEZIER") 
#define ID_CONTROL_COLOR_BEZIER		("*CONTROL_COLOR_BEZIER") 
#define ID_CONTROL_POINT3_SAMPLE	("*CONTROL_POINT3_SAMPLE")

#define ID_CONTROL_FLOAT_TCB	("*CONTROL_FLOAT_TCB") 
#define ID_CONTROL_FLOAT_BEZIER	("*CONTROL_FLOAT_BEZIER") 
#define ID_CONTROL_FLOAT_LINEAR	("*CONTROL_FLOAT_LINEAR") 
#define ID_CONTROL_FLOAT_SAMPLE	("*CONTROL_FLOAT_SAMPLE")

// "Track" is the identification of a sampled controller
#define ID_POS_TRACK			("*CONTROL_POS_TRACK")
#define ID_ROT_TRACK			("*CONTROL_ROT_TRACK") 
#define ID_SCALE_TRACK			("*CONTROL_SCALE_TRACK")

// Sampled keys
#define ID_POS_SAMPLE			("*CONTROL_POS_SAMPLE")
#define ID_ROT_SAMPLE			("*CONTROL_ROT_SAMPLE") 
#define ID_SCALE_SAMPLE			("*CONTROL_SCALE_SAMPLE")

// Specific controller keys
#define ID_POS_KEY				("*CONTROL_POS_KEY")
#define ID_ROT_KEY				("*CONTROL_ROT_KEY") 
#define ID_SCALE_KEY			("*CONTROL_SCALE_KEY")
#define ID_POINT3_KEY			("*CONTROL_POINT3_KEY")
#define ID_FLOAT_KEY			("*CONTROL_FLOAT_KEY")

// TCB Keys have Tens, cont, bias, easeIn, easeOut
#define ID_TCB_POINT3_KEY		("*CONTROL_TCB_POINT3_KEY")
#define ID_TCB_FLOAT_KEY		("*CONTROL_TCB_FLOAT_KEY")
#define ID_TCB_POS_KEY			("*CONTROL_TCB_POS_KEY")
#define ID_TCB_ROT_KEY			("*CONTROL_TCB_ROT_KEY") 
#define ID_TCB_SCALE_KEY		("*CONTROL_TCB_SCALE_KEY")

// Bezier keys have inTan, outTan
#define ID_BEZIER_FLOAT_KEY		("*CONTROL_BEZIER_FLOAT_KEY")
#define ID_BEZIER_POINT3_KEY	("*CONTROL_BEZIER_POINT3_KEY")
#define ID_BEZIER_POS_KEY		("*CONTROL_BEZIER_POS_KEY")
#define ID_BEZIER_SCALE_KEY		("*CONTROL_BEZIER_SCALE_KEY")


#define ID_CONTROL_POS_LINEAR	("*CONTROL_POS_LINEAR")
#define ID_CONTROL_POS_TCB		("*CONTROL_POS_TCB")
#define ID_CONTROL_POS_BEZIER	("*CONTROL_POS_BEZIER")
#define ID_CONTROL_ROT_LINEAR	("*CONTROL_ROT_LINEAR")
#define ID_CONTROL_ROT_TCB		("*CONTROL_ROT_TCB")
#define ID_CONTROL_ROT_BEZIER	("*CONTROL_ROT_BEZIER")
#define ID_CONTROL_SCALE_LINEAR ("*CONTROL_SCALE_LINEAR")
#define ID_CONTROL_SCALE_TCB	("*CONTROL_SCALE_TCB")
#define ID_CONTROL_SCALE_BEZIER	("*CONTROL_SCALE_BEZIER")


// IK Node Info
#define ID_IKTERMINATOR			("*IK_TERMINATOR")
#define ID_IKROT_PINNED			("*IK_ROT_PINNED")
#define ID_IKPOS_PINNED			("*IK_POS_PINNED")

// IK Joints
#define ID_IKJOINT				("*IK_JOINT")
#define ID_IKTYPE				("*IK_TYPE")
#define ID_IKDOF				("*IK_DOF")
#define ID_IKXACTIVE			("*IK_XACTIVE")
#define ID_IKYACTIVE			("*IK_YACTIVE")
#define ID_IKZACTIVE			("*IK_ZACTIVE")
#define ID_IKXLIMITED			("*IK_XLIMITED")
#define ID_IKYLIMITED			("*IK_YLIMITED")
#define ID_IKZLIMITED			("*IK_ZLIMITED")
#define ID_IKXEASE				("*IK_XEASE")
#define ID_IKYEASE				("*IK_YEASE")
#define ID_IKZEASE				("*IK_ZEASE")
#define ID_IKLIMITEXACT			("*IK_LIMITEXACT")
#define ID_IKJOINTINFO			("*IK_JOINTINFO")
#define ID_IKTYPEPOS			("Position")
#define ID_IKTYPEROT			("Rotation")

// Material / Texture related ID's
#define ID_WIRECOLOR			("*WIREFRAME_COLOR") 
#define ID_MATERIAL				("*MATERIAL") 
#define ID_MATERIAL_COUNT		("*MATERIAL_COUNT") 
#define ID_MATERIAL_REF			("*MATERIAL_REF")
#define ID_NUMSUBMTLS			("*NUMSUBMTLS") 
#define ID_SUBMATERIAL			("*SUBMATERIAL") 
#define ID_MATNAME				("*MATERIAL_NAME") 
#define ID_MATCLASS				("*MATERIAL_CLASS")

#define ID_MAT_SHADE_CONST		("Constant")
#define ID_MAT_SHADE_PHONG		("Phong")
#define ID_MAT_SHADE_METAL		("Metal")
#define ID_MAT_SHADE_BLINN		("Blinn")
#define ID_MAT_SHADE_OTHER		("Other")

#define ID_MAP_XPTYPE_FLT		("Filter")
#define ID_MAP_XPTYPE_SUB		("Subtractive")
#define ID_MAP_XPTYPE_ADD		("Additive")
#define ID_MAP_XPTYPE_OTH		("Other")

#define ID_BMP_FILT_PYR			("Pyramidal")
#define ID_BMP_FILT_SAT			("SAT")
#define ID_BMP_FILT_NONE		("None")

#define ID_FALLOFF_OUT			("Out")
#define ID_FALLOFF_IN			("In")
								
#define ID_MAPTYPE_EXP			("Explicit")
#define ID_MAPTYPE_SPH			("Spherical")
#define ID_MAPTYPE_CYL			("Cylindrical")
#define ID_MAPTYPE_SHR			("Shrinkwrap")
#define ID_MAPTYPE_SCR			("Screen")
								
#define ID_AMBIENT				("*MATERIAL_AMBIENT") 
#define ID_DIFFUSE				("*MATERIAL_DIFFUSE") 
#define ID_SPECULAR				("*MATERIAL_SPECULAR") 
#define ID_SHINE				("*MATERIAL_SHINE")
#define ID_SHINE_STRENGTH		("*MATERIAL_SHINESTRENGTH") 
#define ID_TRANSPARENCY			("*MATERIAL_TRANSPARENCY") 
#define ID_WIRESIZE				("*MATERIAL_WIRESIZE")
								
#define ID_SHADING				("*MATERIAL_SHADING") 
#define ID_XP_FALLOFF			("*MATERIAL_XP_FALLOFF") 
#define ID_SELFILLUM			("*MATERIAL_SELFILLUM") 
#define ID_TWOSIDED				("*MATERIAL_TWOSIDED") 
#define ID_WIRE					("*MATERIAL_WIRE")
#define ID_WIREUNITS			("*MATERIAL_WIREUNITS") 
#define ID_FALLOFF				("*MATERIAL_FALLOFF") 
#define ID_FACEMAP				("*MATERIAL_FACEMAP") 
#define ID_SOFTEN				("*MATERIAL_SOFTEN") 
#define ID_XP_TYPE				("*MATERIAL_XP_TYPE")
								
#define ID_TEXNAME				("*MAP_NAME") 
#define ID_TEXCLASS				("*MAP_CLASS") 
#define ID_TEXSUBNO				("*MAP_SUBNO") 
#define ID_TEXAMOUNT			("*MAP_AMOUNT")
								
#define ID_BITMAP				("*BITMAP")
#define ID_TEX_INVERT			("*BITMAP_INVERT") 
#define ID_BMP_FILTER			("*BITMAP_FILTER")
								
#define ID_MAPTYPE				("*MAP_TYPE") 
#define ID_U_OFFSET				("*UVW_U_OFFSET") 
#define ID_V_OFFSET				("*UVW_V_OFFSET") 
#define ID_U_TILING				("*UVW_U_TILING") 
#define ID_V_TILING				("*UVW_V_TILING") 
#define ID_ANGLE				("*UVW_ANGLE") 
#define ID_BLUR					("*UVW_BLUR")
#define ID_BLUR_OFFSET			("*UVW_BLUR_OFFSET") 
#define ID_NOISE_AMT			("*UVW_NOUSE_AMT") 
#define ID_NOISE_SIZE			("*UVW_NOISE_SIZE") 
#define ID_NOISE_LEVEL			("*UVW_NOISE_LEVEL") 
#define ID_NOISE_PHASE			("*UVW_NOISE_PHASE")
								
// Sub texture types			
#define ID_MAP_GENERIC			("*MAP_GENERIC") 
#define ID_MAP_AMBIENT			("*MAP_AMBIENT") 
#define ID_MAP_DIFFUSE			("*MAP_DIFFUSE") 
#define ID_MAP_SPECULAR			("*MAP_SPECULAR") 
#define ID_MAP_SHINE			("*MAP_SHINE")
#define ID_MAP_SHINESTRENGTH	("*MAP_SHINESTRENGTH") 
#define ID_MAP_SELFILLUM		("*MAP_SELFILLUM") 
#define ID_MAP_OPACITY			("*MAP_OPACITY")
#define ID_MAP_FILTERCOLOR		("*MAP_FILTERCOLOR") 
#define ID_MAP_BUMP				("*MAP_BUMP")
#define ID_MAP_REFLECT			("*MAP_REFLECT") 
#define ID_MAP_REFRACT			("*MAP_REFRACT")
								
// TM related ID's				
#define ID_TM_ROW0				("*TM_ROW0") 
#define ID_TM_ROW1				("*TM_ROW1") 
#define ID_TM_ROW2				("*TM_ROW2") 
#define ID_TM_ROW3				("*TM_ROW3") 
#define ID_TM_POS				("*TM_POS")
#define ID_TM_ROTAXIS			("*TM_ROTAXIS") 
#define ID_TM_ROTANGLE			("*TM_ROTANGLE") 
#define ID_TM_SCALE				("*TM_SCALE") 
#define ID_TM_SCALEAXIS			("*TM_SCALEAXIS")
#define ID_TM_SCALEAXISANG		("*TM_SCALEAXISANG") 
#define ID_TM_ANIMATION			("*TM_ANIMATION")

// TM Inheritance flags
#define ID_INHERIT_POS			("*INHERIT_POS")
#define ID_INHERIT_ROT			("*INHERIT_ROT")
#define ID_INHERIT_SCL			("*INHERIT_SCL")

// Scene related ID's			
#define ID_FILENAME				("*SCENE_FILENAME") 
#define ID_FIRSTFRAME			("*SCENE_FIRSTFRAME") 
#define ID_LASTFRAME			("*SCENE_LASTFRAME") 
#define ID_FRAMESPEED			("*SCENE_FRAMESPEED") 
#define ID_TICKSPERFRAME		("*SCENE_TICKSPERFRAME") 
#define ID_ENVMAP				("*SCENE_ENVMAP")
#define ID_STATICBGCOLOR		("*SCENE_BACKGROUND_STATIC") 
#define ID_ANIMBGCOLOR			("*SCENE_BACKGROUND_ANIM") 
#define ID_STATICAMBIENT		("*SCENE_AMBIENT_STATIC") 
#define ID_ANIMAMBIENT			("*SCENE_AMBIENT_ANIM")

#define ID_VISIBILITY_TRACK		("*NODE_VISIBILITY_TRACK")

// Generic ID's that can show up here and there 
#define ID_TIMEVALUE			("*TIMEVALUE")
#define ID_COMMENT				("*COMMENT")
#define ID_FILEID				("*3DSMAX_ASCIIEXPORT")
#define ID_BOUNDINGBOX_MIN		("*BOUNDINGBOX_MIN")
#define ID_BOUNDINGBOX_MAX		("*BOUNDINGBOX_MAX")

