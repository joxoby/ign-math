/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _IGNITION_FRAME_GRAPH_HH_
#define _IGNITION_FRAME_GRAPH_HH_

#include <string>

#include <ignition/math/Types.hh>

#include "FrameException.hh"
#include "Frame.hh"
#include "RelativePose.hh"

namespace ignition
{
  namespace math
  {
    // Forward declaration of private data
    class FrameGraphPrivate;
    using FrameGraphPrivatePtr = std::unique_ptr<FrameGraphPrivate>;

    /// \brief A collection of Frames, and their relative poses.
    class IGNITION_VISIBLE FrameGraph
    {
      /// \brief Default constructor. With the following default values:
      public: FrameGraph();

      /// \brief Destructor
      public: virtual ~FrameGraph();

      /// \brief Prevent copy construction
      public: FrameGraph(const FrameGraph &_x) = delete;

      /// \brief Prevent assignment
      public: FrameGraph &operator=(const FrameGraph &_x) = delete;

      /// \brief Adds a new frame to the graph
      /// \param[in] _path The full path of the frame's parent
      /// \param[in] _name The name of the new frame
      /// \param[in] _pose The pose of the frame, relative to the parent frame
      /// \throws FrameException if one of the path is invalid.
      public: void AddFrame(const std::string &_path,
                            const std::string &_name,
                            const Pose3d &_pose);

      /// \brief Removes a frame and all its children.
      /// \param[in] _path The absolute path to the frame
      /// \throws FrameException if the path is invalid
      public: void DeleteFrame(const std::string &_path);

      /// \brief Computes a relative pose between 2 frames
      /// \param[in] _dst The name of the destination frame
      /// \param[in] _src The name of the source frame
      /// \return The pose of _dest in _src's frame
      /// \throws FrameException if one of the path is invalid.
      public: Pose3d Pose(const std::string &_dst,
                          const std::string &_src) const;

      /// \brief Computes the relative pose between 2 frames, using
      /// a RelativePose Instance
      /// \param[in] _relativePose
      /// \return The pose between the 2 frames
      /// \throws FrameException if one of the frames has been deleted.
      public: Pose3d Pose(const RelativePose &_relativePose) const;

      /// \brief Get the pose of a frame (relative to its parent frame)
      /// \param[in] _path The absolute path to the frame
      /// \return The local pose of the frame
      /// \throws FrameException if the path to the frame is invalid.
      public: Pose3d LocalPose(const std::string &_path) const;

      /// \brief Get the pose of a Frame (relative to its parent frame)
      /// param[in] _frame The frame reference
      /// \return The pose of the frame
      public: Pose3d LocalPose(const FrameWeakPtr &_frame) const;

      /// \brief Set the pose of a frame (relative to its parent frame)
      /// \param[in] _path The absolute path to the frame
      /// \param[in] _p The new local pose
      /// \return The local pose
      /// \throws FrameException if the path to the frame is invalid.
      public: void SetLocalPose(const std::string &_path, const Pose3d &_p);

      /// \brief Set the pose of a frame (relative to its parent frame)
      /// \param[in] _frame The frame reference
      /// \param[in] _p The new pose
      /// \return The local pose
      /// \throws FrameException if the frame has been deleted.
      public: void SetLocalPose(FrameWeakPtr _frame, const Pose3d &_p);

      /// \brief This method generates a relative pose between two frames.
      /// \param[in] _dstPath The destination frame (must be absolute)
      /// \param[in] _srcPath The source frame path (can be relative)
      /// \return A relative pose instance
      /// \throws FrameException if the paths are not invalid.
      public: RelativePose CreateRelativePose(const std::string &_dstPath,
                  const std::string &_srcPath) const;

      /// \brief Get a reference to a frame instance
      /// \param[in] _path The absolute path to the frame
      /// \return The frame's weak pointer
      /// \throws FrameException if the path to the frame is invalid.
      public: FrameWeakPtr Frame(const std::string &_path) const;

      /// \brief Get a reference to a frame instance
      /// \param[in] _frame The start Frame
      /// \param[in] _relativepath The relative path to the frame
      /// \return The frame's weak pointer
      /// \throws FrameException if the path or the frame is invalid.
      public: FrameWeakPtr Frame(FrameWeakPtr _frame,
                                       const std::string &_relativePath) const;

      /// \internal
      /// \brief Private data pointer
      private: FrameGraphPrivatePtr dataPtr;
    };
  }
}
#endif
