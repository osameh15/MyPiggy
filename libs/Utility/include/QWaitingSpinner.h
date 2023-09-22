#ifndef QWAITINGSPINNER_H
#define QWAITINGSPINNER_H

#pragma once

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The QWaitingSpinner class represents a custom widget for displaying a waiting spinner.
 *
 * @author Datall Co, Eagle_Ir
 * @date July 2023
 */

#include <QWidget>
#include <QTimer>
#include <QColor>

/**
 * @brief The QWaitingSpinner class represents a custom widget for displaying a waiting spinner.
 *
 * The QWaitingSpinner widget can be used to indicate that a process is in progress by displaying
 * a spinning animation. It is a subclass of QWidget and provides customizable options for the
 * appearance and behavior of the spinner.
 */
class QWaitingSpinner: public QWidget
{
    Q_OBJECT

public:
    /*! Constructor for "standard" widget behaviour - use this
     * constructor if you wish to, e.g. embed your widget in another. */
    QWaitingSpinner(QWidget *parent                    = 0,
                    bool     centerOnParent            = true,
                    bool     disableParentWhenSpinning = true);

    /*! Constructor - use this constructor to automatically create a modal
     * ("blocking") spinner on top of the calling widget/window.  If a valid
     * parent widget is provided, "centreOnParent" will ensure that
     * QWaitingSpinner automatically centres itself on it, if not,
     * "centreOnParent" is ignored. */
    QWaitingSpinner(Qt::WindowModality modality,
                    QWidget           *parent                    = 0,
                    bool               centerOnParent            = true,
                    bool               disableParentWhenSpinning = true);

    /**
     * @brief Sets the color of the waiting spinner.
     * @param color The color to set.
     */
    void           setColor(QColor color);

    /**
     * @brief Sets the roundness of the waiting spinner.
     * @param roundness The roundness value to set.
     */
    void           setRoundness(qreal roundness);

    /**
     * @brief Sets the minimum trail opacity of the waiting spinner.
     * @param minimumTrailOpacity The minimum trail opacity value to set.
     */
    void           setMinimumTrailOpacity(qreal minimumTrailOpacity);

    /**
     * @brief Sets the trail fade percentage of the waiting spinner.
     * @param trail The trail fade percentage value to set.
     */
    void           setTrailFadePercentage(qreal trail);

    /**
     * @brief Sets the revolutions per second of the waiting spinner.
     * @param revolutionsPerSecond The revolutions per second value to set.
     */
    void           setRevolutionsPerSecond(qreal revolutionsPerSecond);

    /**
     * @brief Sets the number of lines of the waiting spinner.
     * @param lines The number of lines to set.
     */
    void           setNumberOfLines(int lines);

    /**
     * @brief Sets the line length of the waiting spinner.
     * @param length The line length to set.
     */
    void           setLineLength(int length);

    /**
     * @brief Sets the line width of the waiting spinner.
     * @param width The line width to set.
     */
    void           setLineWidth(int width);

    /**
     * @brief Sets the inner radius of the waiting spinner.
     * @param radius The inner radius to set.
     */
    void           setInnerRadius(int radius);

    /**
     * @brief Sets the text of the waiting spinner.
     * @param text The text to set.
     */
    void           setText(QString text);

    /**
     * @brief Retrieves the color of the waiting spinner.
     * @return The color of the waiting spinner.
     */
    QColor         color();

    /**
     * @brief Retrieves the roundness of the waiting spinner.
     * @return The roundness of the waiting spinner.
     */
    qreal          roundness();

    /**
     * @brief Retrieves the minimum trail opacity of the waiting spinner.
     * @return The minimum trail opacity of the waiting spinner.
     */
    qreal          minimumTrailOpacity();

    /**
     * @brief Retrieves the trail fade percentage of the waiting spinner.
     * @return The trail fade percentage of the waiting spinner.
     */
    qreal          trailFadePercentage();

    /**
     * @brief Retrieves the revolutions per second of the waiting spinner.
     * @return The revolutions per second of the waiting spinner.
     */
    qreal          revolutionsPersSecond();

    /**
     * @brief Retrieves the number of lines of the waiting spinner.
     * @return The number of lines of the waiting spinner.
     */
    int            numberOfLines();

    /**
     * @brief Retrieves the line length of the waiting spinner.
     * @return The line length of the waiting spinner.
     */
    int            lineLength();

    /**
     * @brief Retrieves the line width of the waiting spinner.
     * @return The line width of the waiting spinner.
     */
    int            lineWidth();

    /**
     * @brief Retrieves the inner radius of the waiting spinner.
     * @return The inner radius of the waiting spinner.
     */
    int            innerRadius();

    /**
     * @brief Checks if the waiting spinner is currently spinning.
     * @return `true` if the waiting spinner is spinning, `false` otherwise.
     */
    bool           isSpinning() const;

public slots:
    /**
     * @brief Starts the waiting spinner animation.
     * Calling this slot will initiate the spinning animation of the waiting spinner.
     */
    void           start();

    /**
     * @brief Stops the waiting spinner animation.
     * Calling this slot will stop the spinning animation of the waiting spinner.
     */
    void           stop();

private slots:
    /**
     * @brief Slot for rotating the waiting spinner.
     */
    void           rotate();

protected:
    /**
     * @brief Reimplemented from QWidget. Paints the waiting spinner.
     * @param paintEvent The paint event.
     */
    void           paintEvent(QPaintEvent *paintEvent);

private:
    /**
     * @brief Calculates the distance of a line from the primary line.
     * @param current The current line index.
     * @param primary The index of the primary line.
     * @param totalNrOfLines The total number of lines.
     * @return The distance of the line from the primary line.
     */
    static int     lineCountDistanceFromPrimary(int current, int primary,
                                                int totalNrOfLines);

    /**
     * @brief Calculates the color of the current line.
     * @param distance The distance of the line from the primary line.
     * @param totalNrOfLines The total number of lines.
     * @param trailFadePerc The trail fade percentage.
     * @param minOpacity The minimum opacity.
     * @param color The base color.
     * @return The color of the current line.
     */
    static QColor  currentLineColor(int distance, int totalNrOfLines,
                                    qreal trailFadePerc, qreal minOpacity,
                                    QColor color);

    /**
     * @brief Initializes the waiting spinner.
     */
    void  initialize();

    /**
     * @brief Updates the size of the waiting spinner.
     */
    void  updateSize();

    /**
     * @brief Updates the timer of the waiting spinner.
     */
    void  updateTimer();

    /**
     * @brief Updates the position of the waiting spinner.
     */
    void  updatePosition();

    /**
     * @brief QWaitingSpinner: Disallow copy constructor and assignment operator
     */
    QWaitingSpinner(const QWaitingSpinner &);

    /**
     * @brief Disallow assignment operator
     * @return
     */
    QWaitingSpinner& operator=(const QWaitingSpinner &);

private:
    /**
     * @brief The color of the waiting spinner.
     */
    QColor  m_color;

    /**
     * @brief The roundness of the waiting spinner.
     */
    qreal  m_roundness;

    /**
     * @brief The minimum opacity of the trailing lines of the waiting spinner.
     */
    qreal  m_minimumTrailOpacity;

    /**
     * @brief The fade percentage of the trailing lines of the waiting spinner.
     */
    qreal  m_trailFadePercentage;

    /**
     * @brief The number of revolutions per second of the waiting spinner.
     */
    qreal  m_revolutionsPerSecond;

    /**
     * @brief The number of lines in the waiting spinner.
     */
    int  m_numberOfLines;

    /**
     * @brief The length of the lines in the waiting spinner.
     */
    int  m_lineLength;

    /**
     * @brief The width of the lines in the waiting spinner.
     */
    int  m_lineWidth;

    /**
     * @brief The inner radius of the waiting spinner.
     */
    int  m_innerRadius;

    /**
     * @brief The timer for updating the waiting spinner.
     */
    QTimer *m_timer;

    /**
     * @brief Flag indicating whether to center the waiting spinner on its parent.
     */
    bool  m_centerOnParent;

    /**
     * @brief Flag indicating whether to disable the parent widget when the spinner is spinning.
     */
    bool  m_disableParentWhenSpinning;

    /**
     * @brief The current counter value of the waiting spinner.
     */
    int  m_currentCounter;

    /**
     * @brief Flag indicating whether the waiting spinner is currently spinning.
     */
    bool  m_isSpinning;
};

#endif //QWAITINGSPINNER_H
