#ifndef BUILD_INFO_H
#define BUILD_INFO_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The BuildInfo class provides static methods to retrieve build information.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QString>

/**
 * @brief The BuildInfo class provides static methods to retrieve build information.
 */
class BuildInfo
{
public:
    /**
     * @brief Constructs a BuildInfo object.
     */
    BuildInfo();

    /**
     * @brief Retrieves the build time.
     * @return The build time as a QString.
     */
    static QString  getBuildTime();

    /**
     * @brief Retrieves the Git SHA-1 hash.
     * @return The Git SHA-1 hash as a QString.
     */
    static QString  getGitSHA1();

    /**
     * @brief Retrieves the version.
     * @return The version as a QString.
     */
    static QString  getVersion();

    /**
     * @brief Retrieves the Qt version.
     * @return The Qt version as a QString.
     */
    static QString  getQtVersion();
};

#endif // BUILD_INFO_H
