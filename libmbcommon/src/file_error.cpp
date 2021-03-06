/*
 * Copyright (C) 2017  Andrew Gunnerson <andrewgunnerson@gmail.com>
 *
 * This file is part of DualBootPatcher
 *
 * DualBootPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DualBootPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DualBootPatcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mbcommon/file_error.h"

namespace mb
{

struct FileErrorCategory : std::error_category
{
    const char * name() const noexcept override;

    std::string message(int ev) const override;

    virtual std::error_condition
    default_error_condition(int code) const noexcept override;

    //virtual bool
    //equivalent(int code,
    //           const std::error_condition &condition) const noexcept override;
    //virtual bool
    //equivalent(const std::error_code &code,
    //           int condition) const noexcept override;
};

const std::error_category & file_error_category()
{
    static FileErrorCategory c;
    return c;
}

std::error_code make_error_code(FileError e)
{
    return {static_cast<int>(e), file_error_category()};
}

std::error_condition make_error_condition(FileError e)
{
    return {static_cast<int>(e), file_error_category()};
}

const char * FileErrorCategory::name() const noexcept
{
    return "file";
}

std::string FileErrorCategory::message(int condition) const
{
    switch (static_cast<FileError>(condition)) {
    case FileError::ArgumentOutOfRange:
        return "argument out of range";
    case FileError::CannotConvertEncoding:
        return "cannot convert string encoding";
    case FileError::InvalidState:
        return "invalid state";
    case FileError::UnsupportedRead:
        return "read not supported";
    case FileError::UnsupportedWrite:
        return "write not supported";
    case FileError::UnsupportedSeek:
        return "seek not supported";
    case FileError::UnsupportedTruncate:
        return "truncate not supported";
    case FileError::IntegerOverflow:
        return "integer overflowed";
    case FileError::BadFileFormat:
        return "bad file format";
    // Groups
    case FileError::InvalidArgument:
        return "(invalid argument)";
    case FileError::Unsupported:
        return "(unsupported operation)";
    default:
        return "(unknown file error)";
    }
}

std::error_condition
FileErrorCategory::default_error_condition(int code) const noexcept
{
    switch (static_cast<FileError>(code)) {
    case FileError::ArgumentOutOfRange:
    case FileError::CannotConvertEncoding:
        return FileError::InvalidArgument;
    case FileError::UnsupportedRead:
    case FileError::UnsupportedWrite:
    case FileError::UnsupportedSeek:
    case FileError::UnsupportedTruncate:
        return FileError::Unsupported;
    default:
        return std::error_condition(code, *this);
    }
}

}
