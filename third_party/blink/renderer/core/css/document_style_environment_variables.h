// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_DOCUMENT_STYLE_ENVIRONMENT_VARIABLES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_DOCUMENT_STYLE_ENVIRONMENT_VARIABLES_H_

#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/css/style_environment_variables.h"

namespace blink {

class Document;

// DocumentStyleEnvironmentVariables is bound 1:1 to a document and provides
// document level invalidation logic.
class CORE_EXPORT DocumentStyleEnvironmentVariables
    : public StyleEnvironmentVariables {
 public:
  // Create an instance bound to |parent| that will invalidate |document|'s
  // style when a variable is changed.
  static scoped_refptr<DocumentStyleEnvironmentVariables> Create(
      StyleEnvironmentVariables& parent,
      Document& document);

  // Resolve the variable |name| and return the data. This will also cause
  // future changes to this variable to invalidate the associated document's
  // style.
  CSSVariableData* ResolveVariable(const AtomicString& name) override;

 protected:
  // Called when variable |name| is changed. This will notify any children that
  // this variable has changed.
  void InvalidateVariable(const AtomicString& name) override;

 private:
  DocumentStyleEnvironmentVariables(Document& document);

  HashSet<AtomicString> seen_variables_;
  Persistent<Document> document_;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_DOCUMENT_STYLE_ENVIRONMENT_VARIABLES_H_
