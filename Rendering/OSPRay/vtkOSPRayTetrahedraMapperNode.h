/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkOSPRayTetrahedraMapperNode.h

  Copyright (c) Carson Brownlee, Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkOSPRayTetrahedraMapperNode
 * @brief   Unstructured grid volume renderer.
 *
 * vtkOSPRayTetrahedraMapperNode impliments a volume rendering
 * that directly samples the AMR structure using OSPRay.
 *
*/

#ifndef vtkOSPRayTetrahedraMapperNode_h
#define vtkOSPRayTetrahedraMapperNode_h

#include "vtkRenderingOSPRayModule.h" // For export macro
#include "vtkVolumeMapperNode.h"

class vtkFloatArray;
class vtkPoints;
class vtkUnsignedCharArray;
class vtkVisibilitySort;
class vtkVolumeProperty;
class vtkRenderWindow;
class vtkAbstractArray;
class vtkDataSet;

namespace osp
{
  struct TransferFunction;
  struct Volume;
  struct vec3f;
}

class VTKRENDERINGVOLUME_EXPORT vtkOSPRayTetrahedraMapperNode : public vtkVolumeMapperNode

{
public:
  vtkTypeMacro(vtkOSPRayTetrahedraMapperNode,
                       vtkVolumeMapperNode);
  static vtkOSPRayTetrahedraMapperNode *New();
  void PrintSelf(ostream &os, vtkIndent indent) VTK_OVERRIDE;

  /**
   * Make ospray calls to render me.
   */
  virtual void Render(bool prepass) VTK_OVERRIDE;

protected:
  vtkOSPRayTetrahedraMapperNode();
  ~vtkOSPRayTetrahedraMapperNode() VTK_OVERRIDE;

  int NumColors;
  double SamplingRate;

  vtkTimeStamp BuildTime;
  vtkTimeStamp PropertyTime;

  osp::Volume* OSPRayVolume;
  osp::TransferFunction* TransferFunction;
  std::vector<float> TFVals;
  std::vector<float> TFOVals;

  vtkAbstractArray *GetArrayToProcess
    (vtkDataSet* input, int& association);

  std::vector<int> cells;
  std::vector<osp::vec3f> vertices;
  std::vector<float> field;

private:
  vtkOSPRayTetrahedraMapperNode(const vtkOSPRayTetrahedraMapperNode&) VTK_DELETE_FUNCTION;
  void operator=(const vtkOSPRayTetrahedraMapperNode &) VTK_DELETE_FUNCTION;
};

#endif
