/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ecma-builtins.h"
#include "ecma-exceptions.h"
#include "ecma-gc.h"
#include "ecma-globals.h"
#include "ecma-helpers.h"
#include "ecma-typedarray-object.h"

#include "jrt.h"

#if JERRY_BUILTIN_TYPEDARRAY
#if JERRY_BUILTIN_BIGINT

#define ECMA_BUILTINS_INTERNAL
#include "ecma-builtins-internal.h"

#define BUILTIN_INC_HEADER_NAME "ecma-builtin-bigint64array.inc.h"
#define BUILTIN_UNDERSCORED_ID  bigint64array
#include "ecma-builtin-internal-routines-template.inc.h"
#include "ecma-builtin-typedarray-helpers.h"

/** \addtogroup ecma ECMA
 * @{
 *
 * \addtogroup ecmabuiltins
 * @{
 *
 * \addtogroup bigint64array ECMA BigInt64Array object built-in
 * @{
 */

/**
 * Handle calling [[Call]] of BigInt64Array
 *
 * @return ecma value
 */
ecma_value_t
ecma_builtin_bigint64array_dispatch_call(const ecma_value_t *arguments_list_p,  /**< arguments list */
        uint32_t arguments_list_len) /**< number of arguments */
{
    JERRY_ASSERT(arguments_list_len == 0 || arguments_list_p != NULL);

    return ecma_raise_type_error(ECMA_ERR_MSG("Constructor BigInt64Array requires 'new'"));
} /* ecma_builtin_bigint64array_dispatch_call */

/**
 * Handle calling [[Construct]] of BigInt64Array
 *
 * @return ecma value
 */
ecma_value_t
ecma_builtin_bigint64array_dispatch_construct(const ecma_value_t *arguments_list_p,  /**< arguments list */
        uint32_t arguments_list_len) /**< number of arguments */
{
    return ecma_typedarray_helper_dispatch_construct(arguments_list_p, arguments_list_len, ECMA_BIGINT64_ARRAY);
} /* ecma_builtin_bigint64array_dispatch_construct */

/**
 * @}
 * @}
 * @}
 */

#endif /* JERRY_BUILTIN_BIGINT */
#endif /* JERRY_BUILTIN_TYPEDARRAY */
